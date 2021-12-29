#include "../headers/BBox.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

bool BBoxContainsPoint(BBox * bbox, Point * point) {
    if (bbox->minX > point->x) return false;
    if (bbox->minY > point->y) return false;
    if (bbox->maxX < point->x) return false;
    if (bbox->maxY < point->y) return false;
    return true;
}

bool BBoxIntersectsPolygon(BBox * bbox, Polygon * polygon) {
    fprintf(stderr,"BBoxIntersectsPolygon has not been implemented");    
    return false;
}

typedef struct closestFaceResult {
    faceDirection direction;
    double bottomLeft;
    double topLeft;
    double bottomRight;
    double topRight;
    double closestVertexDistance;
}closestFaceResult;

/** 
 * This is also defined in RTree, perhaps 
 * share them?
 * */
int cmpfuncdpointer (const void * a, const void * b) {
   return ( **(double**)a - **(double**)b );
}

closestFaceResult determineClosestFace(BBox * bbox, Point * point) {
    Point * bottomLeft = createPoint(bbox->minX,bbox->minY);
    Point * topLeft = createPoint(bbox->minX,bbox->maxY);
    Point * bottomRight = createPoint(bbox->maxX,bbox->minY);
    Point * topRight = createPoint(bbox->maxX,bbox->maxY);

    double bottomLeftDist = distanceBetweenPoints(point,bottomLeft);
    double topLeftDist = distanceBetweenPoints(point,topLeft);
    double bottomRightDist = distanceBetweenPoints(point,bottomRight);
    double topRightDist = distanceBetweenPoints(point,topRight);

    double * distances[] = {&bottomLeftDist,&topLeftDist,&bottomRightDist,&topRightDist};

    qsort(distances, 4, sizeof(double), cmpfuncdpointer);

    double * shortestDist = distances[0];
    double * secondShortestDist = distances[1];

    faceDirection faceDirectionResult = ERROR;

    if ((shortestDist == &bottomLeftDist && secondShortestDist == &bottomRightDist) || (shortestDist == &bottomRightDist && secondShortestDist == &bottomLeftDist )) {
        faceDirectionResult= BOTTOM;
    } 
    else if ((shortestDist == &bottomLeftDist && secondShortestDist == &topLeftDist) || (shortestDist == &topLeftDist && secondShortestDist == &bottomLeftDist)) {
        faceDirectionResult= LEFT;
    }
    else if((shortestDist == &topLeftDist && secondShortestDist == &topRightDist) || (shortestDist == &topRightDist && secondShortestDist == &topLeftDist)) {
        faceDirectionResult = TOP;
    }
    // Technically now we could just free + return "RIGHT" but just to double check if something is wrong.
    else if ((shortestDist == &topRightDist && secondShortestDist == &bottomRightDist) || (shortestDist == &bottomRightDist && secondShortestDist == &topRightDist)) {
        faceDirectionResult= RIGHT;
    }
    
    assert(faceDirectionResult != ERROR);

    free(bottomLeft);
    free(topLeft);
    free(bottomRight);
    free(topRight);
    closestFaceResult calcResult = {.direction=faceDirectionResult,.bottomLeft=bottomLeftDist,.bottomRight=bottomRightDist,.topLeft=topLeftDist,.topRight=topRightDist,.closestVertexDistance=*shortestDist};
    return calcResult;
}


bool pointWithinXBounds(BBox * bbox, Point * point) {
    if (point->x < bbox->minX) return false;
    if (point->x > bbox->maxX) return false;
    return true;
}

bool pointWithinYBounds(BBox * bbox, Point * point) {
    if (point->y < bbox->minY) return false;
    if (point->y > bbox->maxY) return false;
    return true;
}

double bboxDistanceToPoint(BBox * bbox, Point * point) {
    
    if (BBoxContainsPoint(bbox,point) == true) {
        return 0.0;
    }
    closestFaceResult result = determineClosestFace(bbox,point);
    double distanceResult;
    switch (result.direction)
    {
        case TOP:
            if (pointWithinXBounds(bbox,point)) {
                distanceResult = point->y - bbox->maxY;
            } else {
            distanceResult = result.closestVertexDistance;
            }
            break;
        case BOTTOM:
            if (pointWithinXBounds(bbox,point)) {
                distanceResult = bbox->minY - point->y;
            } else {
            distanceResult = result.closestVertexDistance;
            }
            break;
        case RIGHT:
            if (pointWithinYBounds(bbox,point)) {
                distanceResult = point->x - bbox->maxX;
            } else {
            distanceResult = result.closestVertexDistance;
            }
            break;
        case LEFT:
            if (pointWithinYBounds(bbox,point)) {
                distanceResult = bbox->minX - point->x;
            } else {
            distanceResult = result.closestVertexDistance;
            }
            break;
        default:
            fprintf(stderr,"Invalid face direction result");
            exit(1);
            break;
    }
    
    return distanceResult;
}