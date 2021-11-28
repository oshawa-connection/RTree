#include "../headers/Node.h"
#include "../headers/BBox.h"
#include <stdlib.h>

const int MAX_POINTS_PER_NODE = 10;

typedef struct Node {
    Point * points;
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

bool addPointToNode(NodePtr node,Point * point) {
    if (node->nNodes >= MAX_POINTS_PER_NODE) {

    }
}

// NodeSplitResult * splitNode(NodePtr node) {
//     malloc(sizeof)
// }

BBox * getNodeBBox(NodePtr node) {
    return node->bbox;
}

int getChildNodeCount(NodePtr node) {
    return node->nNodes;
}