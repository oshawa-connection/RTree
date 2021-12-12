#pragma once
#include <stdio.h>
#include "BBox.h"
#include "types.h"
#include "Node.h"

typedef struct RTree * RTreePtr;



RTreePtr createRTree();

void deleteRTree(RTreePtr* rtree);

int getRTreeDepth(RTreePtr rtree);


/**
 * 
 * */
void RTreeInsertPoint(RTreePtr rTree, Point * newPoint);


/**
 * 
 * */
void _rTreeSearch(RTreePtr rTree, NodePtr queryNode);

