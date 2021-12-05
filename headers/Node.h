#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "./BBox.h"

// Needed in header to allow testing
# define MAX_POINTS_PER_NODE 10

typedef struct Node * NodePtr;

/**
 * They are called left and right but
 * actually they could be split in either direction.
 * */
typedef struct NodeSplitResult {
    NodePtr * leftNode;
    NodePtr * rightNode;
} NodeSplitResult;



NodePtr createNode(BBox * bbox);

void deleteNode(NodePtr node);

bool nodeIsLeaf(NodePtr node);

NodePtr getChildNodeAt(NodePtr node, int childNodeIndex);

BBox * getNodeBBox(NodePtr node);