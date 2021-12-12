#include "../headers/Node.h"
#include "../headers/BBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {X_DIRECTION,Y_DIRECTION} splitDirection;

typedef struct Node {
    Point ** points;
    int nPoints;
    int nNodes;
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



NodePtr getChildNodeAt(NodePtr node, int childNodeIndex) {
    if (node->points == NULL) {
        return NULL;
    }
    if (childNodeIndex > node->nPoints) {
        return NULL;
    }
    return node->nextNodes[childNodeIndex];
}

//TODO: CALL BboxEnlargen
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

    node->nPoints += 1;
    return true;
}

BBox * getNodeBBox(NodePtr node) {
    return node->bbox;
}

int getChildNodeCount(NodePtr node) {
    return node->nNodes;
}

NodeSplitResult * createNodeSplitResult() {
    NodeSplitResult * splitResult = (NodeSplitResult *) malloc(sizeof(NodeSplitResult *));
    splitResult->error = false;
    splitResult->leftNode = NULL;
    splitResult->rightNode = NULL;
    return splitResult;
}

void destroyNodeSplitResult(NodeSplitResult * nodeSplitresult) {
    if (nodeSplitresult->leftNode != NULL) {
        free(nodeSplitresult->leftNode);
    }
    if (nodeSplitresult->rightNode != NULL) {
        free(nodeSplitresult->rightNode);
    }

    free(nodeSplitresult);
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


NodeSplitResult * splitNode(NodePtr * nodePtr) {
    NodePtr node = *nodePtr;
    NodeSplitResult * splitResult = (NodeSplitResult *) malloc(sizeof(NodeSplitResult *));
    if(node->nPoints <= 3 || node->nNodes != 0) {
        fprintf(stderr, "The node you are trying to split has %d points and %d child nodes so it cannot be split.", node->nPoints, node->nNodes);
        splitResult->error = true;
    }
    
    double * pointXValues = (double *) malloc(sizeof(double) * node->nPoints);
    double * pointYValues = (double *) malloc(sizeof(double) * node->nPoints);

    for(int i =0;i < node->nPoints;i++) {
        pointXValues[i] = node->points[i]->x;
        pointYValues[i] = node->points[i]->y;
    }

    splitDirection result = determineSplitDirection(pointXValues, pointYValues, node->nPoints);
    //Now based on greater varience, split in that direction.

    if (result == X_DIRECTION) {
        double medianX = caculateMediand(pointXValues, node->nPoints);
        BBox * leftbboxPtr = createBBox(0,node->bbox->minX,node->bbox->minY,medianX,node->bbox->maxY);
        BBox * rightbboxPtr = createBBox(0,medianX,node->bbox->minY,node->bbox->maxX,node->bbox->maxY);
        splitResult->leftNode = createNode(leftbboxPtr);
        splitResult->rightNode = createNode(rightbboxPtr);
    } else {
        double medianY = caculateMediand(pointYValues, node->nPoints);
        BBox * leftbboxPtr = createBBox(0,node->bbox->minX,node->bbox->minY,node->bbox->maxX,medianY);
        BBox * rightbboxPtr = createBBox(0,node->bbox->minX,medianY,node->bbox->maxX,node->bbox->maxY);
        splitResult->leftNode = createNode(leftbboxPtr);
        splitResult->rightNode = createNode(rightbboxPtr);
    }
    
    // now distribute points between two new nodes.
    // for (int nodeIndex = 0; nodeIndex < node->nPoints; nodeIndex ++) {
    //     node[]
    // }
    // free the current node and its children!
    // deleteBBox(node->bbox);
    deleteNode(nodePtr);
    free(pointXValues);
    free(pointYValues);
    
    return splitResult;
}


