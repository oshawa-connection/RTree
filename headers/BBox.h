#pragma once
#include "Point.h"
#include "Polygon.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct BBox{
    int id;
    double minX;
    double minY;
    double maxX;
    double maxY;
} BBox;

typedef enum {TOP,BOTTOM,LEFT,RIGHT,ERROR} faceDirection;

// /**
//  * 
//  * */
BBox * createBBox(int id,double minX, double minY, double maxX, double maxY);

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

bool BBoxContainsPoint(BBox * bbox, Point * point);

bool BBoxIntersectsPolygon(BBox * bbox, Polygon * polygon);

double bboxDistanceToPoint(BBox * bbox, Point * point);

void serialiseBBox(FILE * file,BBox * bboxptr);