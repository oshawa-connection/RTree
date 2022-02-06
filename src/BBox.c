#include "../headers/BBox.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static int bboxID = 0;

BBox * createBBox(int id,double minX, double minY, double maxX, double maxY) {
    BBox * myBBox = (BBox *)malloc(sizeof(BBox));
    
    myBBox->id = bboxID;

    bboxID += 1;
    myBBox->minX = minX;
    myBBox->minY = minY;
    myBBox->maxX = maxX;
    myBBox->maxY = maxY;
    return myBBox;
}

void serialiseBBox(FILE * file,BBox * bboxptr) {
    fprintf(file,"[BBOX]\n%d\n%f\n%f\n%f\n%f\n",bboxptr->id,bboxptr->minX,bboxptr->minY,bboxptr->maxX,bboxptr->maxY);

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
/**
 * This function has a bug. If the BBox is really long, then points could be determined to be closest to 
 * the ERROR face - because if it is closest the the topLeft, and the topRight is really far away, then the 
 * bottomLeft could be closer even though the point is above the bbox.
 * 
 * */
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

    qsort(distances, 4, sizeof(double*), cmpfuncdpointer);

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
    

    if (faceDirectionResult == ERROR) {
        fprintf(stderr,"ERROR while determining face direction.\n");
        fprintf(stderr,"Point x: %f, y: %f\n",point->x,point->y);
        fprintf(stderr,"BBOX: minx: %f, miny: %f, maxx: %f, maxy: %f\n",bbox->minX,bbox->minY,bbox->maxX,bbox->maxY);
    }
    assert(faceDirectionResult != ERROR);

    free(bottomLeft);
    free(topLeft);
    free(bottomRight);
    free(topRight);

    closestFaceResult calcResult = {.direction=faceDirectionResult,.bottomLeft=bottomLeftDist,.topLeft=topLeftDist,.bottomRight=bottomRightDist,.topRight=topRightDist,.closestVertexDistance=*shortestDist};
    return calcResult;
}


double determineClosestFaceSecond(BBox * bbox, Point * point) {
    faceDirection faceDirectionResult = ERROR;

    // TOP
    if (point->y > bbox->maxY && point->x < bbox->maxX && point->x > bbox->minX) {
        faceDirectionResult = TOP;
        Point bboxPoint = {point->x,bbox->maxY};
        return distanceBetweenPoints(point,&bboxPoint);
    }

    // BOTTOM
    if (point->y < bbox->maxY && point->x < bbox->maxX && point->x > bbox->minX) {
        faceDirectionResult = BOTTOM;
        Point bboxPoint = {point->x,bbox->minY};
        return distanceBetweenPoints(point,&bboxPoint);
    }

    //LEFT
    if (point->x < bbox->minX && point->y < bbox->maxY && point->y > bbox->minY) {
        faceDirectionResult = LEFT;
        Point bboxPoint = {bbox->minX,point->y};
        return distanceBetweenPoints(point,&bboxPoint);
    }

    // RIGHT
    if (point->x > bbox->maxX && point->y < bbox->maxY && point->y > bbox->minY) {
        faceDirectionResult = RIGHT;
        Point bboxPoint = {bbox->maxX,point->y};
        return distanceBetweenPoints(point,&bboxPoint);
    }

    Point bottomLeft = {bbox->minX,bbox->minY};
    Point bottomRight = {bbox->maxX,bbox->minY};
    Point topLeft = {bbox->minX,bbox->maxY};
    Point topRight = {bbox->maxX,bbox->maxY};

    double bottomLeftDist = distanceBetweenPoints(point,&bottomLeft);
    double bottomRightDist = distanceBetweenPoints(point,&bottomRight);
    double topLeftDist = distanceBetweenPoints(point,&topLeft);
    double topRightDist = distanceBetweenPoints(point,&topRight);

    double * distances[] = {&bottomLeftDist,&bottomRightDist,&topLeftDist,&topRightDist};

    qsort(distances, 4, sizeof(double*), cmpfuncdpointer);
    return *distances[0];
    
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

    //TODO: This is a very inefficient way of doing this.
    // We should probably use a KD-Tree to do this.
    // But for now this is fine.
    // We should also probably use a KD-Tree to do this.
    // But for now this is fine.
    

    return determineClosestFaceSecond(bbox,point);
}