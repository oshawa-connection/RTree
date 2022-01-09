#include "../headers/Node.h"
#include "../headers/BBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <glib.h>

typedef enum {X_DIRECTION,Y_DIRECTION} splitDirection;

typedef struct Node {
    Point ** points;
    size_t nPoints;
    size_t nNodes;
    BBox * bbox;
    NodePtr * nextNodes;
} Node;

NodePtr createNode(BBox * bbox) {
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->nPoints = 0;
    node->nNodes = 0;
    node->nextNodes = NULL;
    node->points = NULL;
    
    node->bbox = bbox;
    return node;
}

// We don't want to free the points or the other nodes, which get split between 
// the two split nodes.
// The bbox does get freed though.
void deleteNode(NodePtr * node) {
    free(*node);
    *node = NULL;
}


bool nodeIsLeaf(Node * node) {
    if (node->nextNodes == NULL) {
        return true;
    }

    return false;
}



NodePtr getChildNodeAt(NodePtr node, size_t childNodeIndex) {
    if (node->nextNodes == NULL) {
        return NULL;
    }
    if (childNodeIndex >= node->nNodes) {
        return NULL;
    }
    return node->nextNodes[childNodeIndex];
}

Point * getPointAt(NodePtr node, size_t pointIndex) {
    if (node->points == NULL) {
        return NULL;
    }
    // Remember that arrays are 0 indexed
    if (pointIndex >= node->nPoints) {
        return NULL;
    }
    return node->points[pointIndex];
}


/**
 * TODO: Allow adding points when this is not a leaf node, 
 * it should just increase the size of BBox. Could do this as a 
 * seperate function if needed. 
 * */
bool addPointToNode(NodePtr node,Point * point) {
    if (node->nPoints >= MAX_POINTS_PER_NODE) {
        // Cannot insert here, requires a split
        return false;
    }
    if (node->nPoints == 0) {
        // Hacky, some compiler options (and CPP) may complain.
        node->points = (Point **) malloc(sizeof(Point **) * MAX_POINTS_PER_NODE);
    }

    node->points[node->nPoints] = point;
    BboxEnlargen(node->bbox,point);
    node->nPoints += 1;
    return true;
}

BBox * getNodeBBox(NodePtr node) {
    return node->bbox;
}

size_t getChildNodeCount(NodePtr node) {
    return node->nNodes;
}

NodeSplitResult * createNodeSplitResult() {
    NodeSplitResult * splitResult = (NodeSplitResult *) malloc(sizeof(NodeSplitResult *));
    splitResult->error = false;
    return splitResult;
}

void destroyNodeSplitResult(NodeSplitResult * nodeSplitresult) {
    free(nodeSplitresult);
}

double calculateMinimumd(GList * pointList, bool y) {
    double currentMin = DBL_MAX;
    size_t numberOfValues = g_list_length(pointList);
    for(size_t i=0;i<numberOfValues;i++) {
        Point * currentPoint =(Point *) g_list_nth_data(pointList,i);
        double currentValue = currentPoint->x;
        if (y) {
            currentValue = currentPoint->y;
        } 
        if (currentValue < currentMin) {
            currentMin = currentValue;
        }
    }
    return currentMin;
}

double calculateMaximumd(GList * pointList, bool y) {
    double currentMax = DBL_MIN;
    size_t numberOfValues = g_list_length(pointList);
    for(size_t i=0;i<numberOfValues;i++) {
        Point * currentPoint =(Point *) g_list_nth_data(pointList,i);
        double currentValue = currentPoint->x;
        if (y) {
            currentValue = currentPoint->y;
        } 
        if (currentValue > currentMax) {
            currentMax = currentValue;
        }
    }
    return currentMax;
}

double calculateMeand(double * dvalues, size_t numberOfValues) {
    double sum;
    for(int i=0;i<numberOfValues;i++) {
        sum += dvalues[i];
    }
    return sum / numberOfValues;
}

double calculateVarienced(double * dvalues, size_t numberOfValues) {
    double sum;
    double mean = calculateMeand(dvalues,numberOfValues);
    for(int i=0;i<numberOfValues;i++) {
        sum += powl(dvalues[i] - mean,2);
    }
    return sum / (numberOfValues -1);
}

// This is a key function. Determining the split direction determines the performance of the RTree for searching.
splitDirection determineSplitDirection(double * pointXValues, double * pointYValues, size_t nValues) {
    double xVarience = calculateVarienced(pointXValues,nValues);
    double yVarience = calculateVarienced(pointYValues, nValues);

    // if they are the same, just return Y.
    if (xVarience > yVarience) {
        return X_DIRECTION;
    } else {
        return Y_DIRECTION;
    }
}

int cmpfuncd (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}

double caculateMediand(double * dvalues, size_t numberOfValues) {
    qsort(dvalues, numberOfValues, sizeof(double), cmpfuncd);
    int middleIndex = ceil(numberOfValues /2 );
    return dvalues[middleIndex];
}


void addSplitResultToNode(NodePtr node, Node * leftNode, Node * rightNode) {
    node->nPoints = 0;
    free(node->points);
    node->points = NULL;
    node->nNodes = 2;
    node->nextNodes = (Node **)malloc(sizeof(Node **) * 2);
    node->nextNodes[0] = leftNode;
    node->nextNodes[1] = rightNode;
}

/**
 * TODO: When splitting, calculate the bounds of the other axis
 * from the points assigned to that bbox. This will account for 
 * cases where the new points aren't in the same X or Y.
 * */
bool splitNode(NodePtr node) {
    // NodeSplitResult * splitResult = (NodeSplitResult *) malloc(sizeof(NodeSplitResult *));
    if(node->nPoints <= 3 || node->nNodes != 0) {
        fprintf(stderr, "The node you are trying to split has %zu points and %zu child nodes so it cannot be split.", node->nPoints, node->nNodes);
        return false;
    }
    
    double * pointXValues = (double *) malloc(sizeof(double) * node->nPoints);
    double * pointYValues = (double *) malloc(sizeof(double) * node->nPoints);
    
    for(size_t i =0;i < node->nPoints;i++) {
        pointXValues[i] = node->points[i]->x;
        pointYValues[i] = node->points[i]->y;
    }

    splitDirection result = determineSplitDirection(pointXValues, pointYValues, node->nPoints);
    //Now based on greater varience, split in that direction.

    Node * leftNode;
    Node * rightNode;
    GList * leftNodeValues = NULL;
    GList * rightNodeValues = NULL;
    BBox * leftbboxPtr;
    BBox * rightbboxPtr;
    // TODO: Perhaps this section could be moved to the bbox.c itself?
    if (result == X_DIRECTION) {
        double medianX = caculateMediand(pointXValues, node->nPoints);

        for (int pointIndex = 0; pointIndex < node->nPoints; pointIndex ++) {
            Point * currentPoint = node->points[pointIndex];
            if (currentPoint->x <= medianX) {
                leftNodeValues = g_list_append(leftNodeValues,currentPoint);
            } else {
                rightNodeValues = g_list_append(rightNodeValues,currentPoint);
            }
        }
        
        double minXLeft = calculateMinimumd(leftNodeValues,false);
        double minYLeft = calculateMinimumd(leftNodeValues,true);
        double maxYLeft = calculateMaximumd(leftNodeValues,true);

        double maxXRight = calculateMaximumd(rightNodeValues,false); 
        double minYRight = calculateMinimumd(rightNodeValues,true);
        double maxYRight = calculateMaximumd(rightNodeValues,true); 

        leftbboxPtr = createBBox(0,minXLeft,minYLeft,medianX,maxYLeft);
        rightbboxPtr = createBBox(0,medianX,minYRight,maxXRight,maxYRight);

        leftNode = createNode(leftbboxPtr);
        rightNode = createNode(rightbboxPtr);
    } else {
        double medianY = caculateMediand(pointYValues, node->nPoints);

        for (int pointIndex = 0; pointIndex < node->nPoints; pointIndex ++) {
            Point * currentPoint = node->points[pointIndex];
            if (currentPoint->y <= medianY) {
                leftNodeValues = g_list_append(leftNodeValues,currentPoint);
            } else {
                rightNodeValues = g_list_append(rightNodeValues,currentPoint);
            }
        }

        double minXLeft = calculateMinimumd(leftNodeValues,false);
        double minYLeft = calculateMinimumd(leftNodeValues,true);
        double maxXLeft = calculateMaximumd(leftNodeValues,false);

        double minXRight = calculateMinimumd(rightNodeValues,false);
        double maxXRight = calculateMaximumd(rightNodeValues,false); 
        double maxYRight = calculateMaximumd(rightNodeValues,true); 

        leftbboxPtr = createBBox(0,minXLeft,minYLeft,maxXLeft,medianY);
        rightbboxPtr = createBBox(0,minXRight,medianY,maxXRight,maxYRight);

        leftNode = createNode(leftbboxPtr);
        rightNode = createNode(rightbboxPtr);
    }
    
    // TODO: switch to using the nodes in the Glist which have done this work for you!
    // now distribute points between two new nodes using the lists.
    for (int pointIndex = 0; pointIndex < node->nPoints; pointIndex ++) {
        Point * currentPoint = node->points[pointIndex];
        if (BBoxContainsPoint(leftNode->bbox,currentPoint)) {
            addPointToNode(leftNode,currentPoint);
        // TODO: Once we are sure this works, remove these parts.
        } else if (BBoxContainsPoint(rightNode->bbox,currentPoint)) {
            addPointToNode(rightNode,currentPoint);
        } else { 
            fprintf(stderr,"Point does not fit into either bbox");
            exit(1);
        }
    }
    
    addSplitResultToNode(node,leftNode,rightNode);

    free(pointXValues);
    free(pointYValues);
    g_list_free(leftNodeValues);
    g_list_free(rightNodeValues);
    return true;
}


bool isCloseToQueryObject(Node * node, Point * queryObject) {
    // node->bbox
    return false;
}

bool nodeEnclosesPoint(NodePtr node, Point * point) {
    return BBoxContainsPoint(node->bbox,point);
}


bool nodeContainsPoint(NodePtr node, Point * point) {
    for(int pointIndex =0;pointIndex < node->nPoints;pointIndex ++) {
        Point * currentPoint = node->points[pointIndex];
        if (pointsAreEqual(currentPoint, point)) {
            return true;
        }
    }
    return false;
}


bool nodeWithinDistance(NodePtr node, Point * point, double distanceLimit) {
    double distance = bboxDistanceToPoint(node->bbox,point);
    return distance < distanceLimit;
}

double distNodeToPoint(NodePtr node, Point * point) {
    return bboxDistanceToPoint(node->bbox,point);
}

/**
 * 
 * */
double trimNodeBBox(NodePtr node) {
    return 0.0;
}