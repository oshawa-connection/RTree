#pragma once

#include <stdlib.h>
#include <stdbool.h>
// -- 
// These are included here because SIZE_MAX is defined in different places on
// linux and mac.
#include <limits.h>
#include <stdint.h>
// --
#include "./BBox.h"
#include "./Point.h"

//TODO: Allow setting at runtime instead.
// Needed in header to allow testing
# define MAX_POINTS_PER_NODE 7
#if MAX_POINTS_PER_NODE >= SIZE_MAX
    #error "MAX_POINTS_PER_NODE exceeds SIZE_MAX of %s", 
#endif
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

NodePtr getChildNodeAt(NodePtr node, size_t childNodeIndex);

Point * getPointAt(NodePtr node, size_t pointIndex);

BBox * getNodeBBox(NodePtr node);

bool splitNode(NodePtr node);

void destroyNodeSplitResult(NodeSplitResult * nodeSplitresult);

/**
 * This checks if the bbox of the node encloses a point, 
 * NOT if it contains the actual point itself.
 * */
bool nodeEnclosesPoint(NodePtr node, Point * point);

bool nodeContainsPoint(NodePtr node, Point * point);


/**
 * Deprecated: use distNodeToPoint instead.
 * */
bool nodeWithinDistance(NodePtr node, Point * point, double distanceLimit);

double distNodeToPoint(NodePtr node, Point * point);

int getNodeBBoxID(NodePtr node);