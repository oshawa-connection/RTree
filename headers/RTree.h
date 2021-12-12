#pragma once
#include <stdio.h>
#include "BBox.h"
#include "types.h"
#include "Node.h"

typedef struct {
    int depth;
    NodePtr rootNode; 
} RTree;

RTree * createRTree();

NodePtr _rTreeTraverseToLeaf(RTree * rTree, Point * point);

/**
 * 
 * */
NodePtr _rTreeInsertPoint(RTree * rTree, Point * newPoint);


/**
 * 
 * */
void _rTreeSearch(RTree * rTree, NodePtr queryNode);

