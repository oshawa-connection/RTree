#pragma once
#include <stdio.h>
#include "BBox.h"
#include <float.h>
#include "types.h"



typedef struct Node {
    Point ** points;
    int nPoints;
    int nNodes;
    BBox * bbox;
    struct Node * nextNodes;
} Node;


typedef struct {
    int depth;
    int maxPointsPerNode;
    Node * rootNode; // does not store points! Only Bboxes!
    BBox * overallBbox;
} RTree;

/**
 * 
 * */
bool _nodeIsALeaf(Node * node);

Node * _rTreeTraverseToLeaf(RTree * rTree, Point * point);

/**
 * 
 * */
Node * _rTreeInsertPoint(RTree * rTree, Point * newPoint);


/**
 * 
 * */
void _rTreeSearch(RTree * rTree, Node * queryNode);

