#pragma once
#include "Point.h"

typedef struct {
    int id;
    float minX;
    float minY;
    float maxX;
    float maxY;
} BBox;

short _BboxContainsPoint(BBox * bbox, Point * point);

float BboxArea(BBox * bbox);
/*
 * Calculates the minimum area needed to expand a bbox to encapsulate a point.
 * */
float BboxMinEnlargementArea(BBox * bbox, Point * point);

void bboxEnlargen(BBox * bbox, Point * point);