#pragma once
#include "Point.h"
#include "Polygon.h"
#include <stdbool.h>
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
BBox * createBBox(int id,float minX, float minY, float maxX, float maxY);

void deleteBBox(BBox * bbxptr);

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

bool BBoxContainsPoint(BBox * bbox, Point * point);

bool BBoxIntersectsPolygon(BBox * bbox, Polygon * polygon);