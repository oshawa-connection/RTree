#include "../headers/Node.h"
#include "../headers/BBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
void deleteNode(NodePtr node) {
    free(node);
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




NodeSplitResult * splitNode(NodePtr node) {
    NodeSplitResult * splitResult = (NodeSplitResult *) malloc(sizeof(NodeSplitResult *));
    if(node->nPoints <= 1) {
        fprintf(stderr, "The node you are trying to split has %d points so it cannot be split.", node->nPoints);
        splitResult->error = true;
    }
    
    double * pointXValues = (double *) malloc(sizeof(double) * node->nPoints);
    double * pointYValues = (double *) malloc(sizeof(double) * node->nPoints);

    for(int i =0;i < node->nPoints;i++) {
        pointXValues[i] = node->points[i]->x;
        pointYValues[i] = node->points[i]->y;
    }

    double xVarience = calculateVarienced(pointXValues,node->nPoints);
    double yVarience = calculateVarienced(pointYValues, node->nPoints);

    BBox * bboxPtr = createBBox(2,2.2,2.2,2.2,3.3);
    //Now based on greater varience, split in that direction.
    splitResult->leftNode = createNode(bboxPtr);
    splitResult->leftNode = createNode(bboxPtr);
    return splitResult;
}


