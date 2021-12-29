#include "../headers/Point.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

Point * createPoint(float x, float y) {
    Point * point = (Point *) malloc(sizeof(Point *));
    point->x = x;
    point->y = y;
    return point;
}

double calcDiff(double a1, double a2) {
    double a = 0;
    if (a1 > a2) {
        a = a2 - a1;   
    } else {
        a = a1 - a2;
    }
    a = pow(a,2);
    return a;
}

double distanceBetweenPoints(Point * point, Point * otherPoint) { 
    // determine a
    double aSquared = calcDiff(point->x,otherPoint->x);
    double bSquared = calcDiff(point->y,otherPoint->y);
    return sqrt(aSquared - bSquared);
}

bool pointsAreEqual(Point * point, Point * otherPoint) {
    double xDiff = fabsf(point->x - otherPoint->x);
    double yDiff = fabsf(point->x - otherPoint->x);
    return xDiff < __FLT_EPSILON__ && yDiff < __FLT_EPSILON__;
}