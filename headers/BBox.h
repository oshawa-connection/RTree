#include "Point.h"

typedef struct {
    float minX;
    float minY;
    float maxX;
    float maxY;
} BBox;

short _BboxContainsPoint(BBox * bbox, Point * point) {
    if (point->x < bbox->minX || point->x > bbox->maxX) {
        return 0;
    }

    if (point->y < bbox->minY || point->y > bbox->maxY) {
        return 0;
    }

    return 1;
}

float BboxArea(BBox * bbox) {
    return (bbox->maxX - bbox->minX) * (bbox->maxY - bbox->minY);
}



/*
 * Calculates the minimum area needed to expand a bbox to encapsulate a point.
 * */
float BboxMinEnlargementArea(BBox * bbox, Point * point) {

    float currentArea = BboxArea(bbox);
    BBox enlargenedBBox = {bbox->minX,bbox->minY,bbox->maxX,bbox->maxY};
    if (point->x > bbox->maxX) {
        enlargenedBBox.maxX = point->x;
    } 

    if (point->x < bbox->minX) {
        enlargenedBBox.minX = point->x;
    }

    if (point->y > bbox->maxY) {
        enlargenedBBox.maxY = point->y;
    }

    if (point->y < bbox->minY) {
        enlargenedBBox.minY = point->y;
    }
    
    return BboxArea(&enlargenedBBox) - currentArea;
    
}

void bboxEnlargen(BBox * bbox, Point * point) {
    if (point->x > bbox->maxX) {
        bbox->maxX = point->x;
    } 

    if (point->x < bbox->minX) {
        bbox->minX = point->x;
    }

    if (point->y > bbox->maxY) {
        bbox->maxY = point->y;
    }

    if (point->y < bbox->minY) {
        bbox->minY = point->y;
    }
}