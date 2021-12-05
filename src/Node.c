#include "../headers/Node.h"
#include "../headers/BBox.h"
#include <stdlib.h>



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
    free(node->bbox);
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

// NodeSplitResult * splitNode(NodePtr node) {
//     malloc(sizeof)
// }

BBox * getNodeBBox(NodePtr node) {
    return node->bbox;
}

int getChildNodeCount(NodePtr node) {
    return node->nNodes;
}