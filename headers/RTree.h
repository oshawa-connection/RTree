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
Point * RTreeFindNearestNeighbour(RTreePtr rTree, Point * queryPoint);


bool RTreecontainsPoint(RTreePtr rTree, Point * point);

void serialiseRTree(RTreePtr rTree, FILE * outputfile);