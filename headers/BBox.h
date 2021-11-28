#pragma once
#include "Point.h"

typedef struct BBox{
    int id;
    float minX;
    float minY;
    float maxX;
    float maxY;
} BBox;

// /**
//  * 
//  * */
// BBox * BBoxNew(int id) {
//     BBox * myBBox = malloc(sizeof *myBBox);
//     return myBBox;
// }

// BBox * BBoxDelete() {
//     BBox * myBBox = malloc(sizeof *myBBox);
//     return myBBox;
// }

float BboxArea(BBox * bbox);
/*
 * Calculates the minimum area needed to expand a bbox to encapsulate a point.
 * */
float BboxMinEnlargementArea(BBox * bbox, Point * point);

void BboxEnlargen(BBox * bbox, Point * point);

void BboxSplit(BBox * bbox,BBox * newBBoxes);