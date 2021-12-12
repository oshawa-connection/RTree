#include "../headers/BBox.h"


BBox * createBBox(int id,float minX, float minY, float maxX, float maxY) {
    BBox * myBBox = (BBox *)malloc(sizeof(BBox));
    myBBox->minX = minX;
    myBBox->minY = minY;
    myBBox->maxX = maxX;
    myBBox->maxY = maxY;
    return myBBox;
}

void deleteBBox(BBox * bbxptr) {
    free(bbxptr);
}

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
    BBox enlargenedBBox = {0,bbox->minX,bbox->minY,bbox->maxX,bbox->maxY};
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

void BboxEnlargen(BBox * bbox, Point * point) {
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

/**
 * Split a bbox into two parts
 * */
void BboxSplit(BBox * bbox, BBox * newBBoxes) {
    
}


bool BBoxContains(BBox * bbox, Point * point) {
    if (bbox->minX > point->x) return false;
    if (bbox->minY > point->y) return false;
    if (bbox->maxX < point->x) return false;
    if (bbox->maxY < point->y) return false;
    return true;
}