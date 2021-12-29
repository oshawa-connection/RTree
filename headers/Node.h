#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "./BBox.h"
#include "./Point.h"

// Needed in header to allow testing
# define MAX_POINTS_PER_NODE 10

typedef struct Node * NodePtr;

/**
 * They are called left and right but
 * actually they could be split in either direction.
 * */
typedef struct NodeSplitResult {
    bool error;
} NodeSplitResult;

bool addPointToNode(NodePtr node,Point * point);

NodePtr createNode(BBox * bbox);

void deleteNode(NodePtr * node);

bool nodeIsLeaf(NodePtr node);

NodePtr getChildNodeAt(NodePtr node, int childNodeIndex);

BBox * getNodeBBox(NodePtr node);

bool splitNode(NodePtr node);

void destroyNodeSplitResult(NodeSplitResult * nodeSplitresult);

/**
 * This checks if the bbox of the node encloses a point, 
 * NOT if it contains the actual point itself.
 * */
bool nodeEnclosesPoint(NodePtr node, Point * point);

bool nodeContainsPoint(NodePtr node, Point * point);