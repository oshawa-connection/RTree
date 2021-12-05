#pragma once
#include <stdio.h>
#include "BBox.h"
#include "types.h"
#include "Node.h"

typedef struct {
    int depth;
    int maxPointsFORNode;
    NodePtr rootNode; // does not store points! Only Bboxes!
    BBox * overallBbox;
} RTree;

/**
 * 
 * */
bool _nodeIsALeaf(NodePtr node);

NodePtr _rTreeTraverseToLeaf(RTree * rTree, Point * point);

/**
 * 
 * */
NodePtr _rTreeInsertPoint(RTree * rTree, Point * newPoint);


/**
 * 
 * */
void _rTreeSearch(RTree * rTree, NodePtr queryNode);

