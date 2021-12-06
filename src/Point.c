#include "../headers/Point.h"

Point * createPoint(float x, float y) {
    Point * point = (Point *) malloc(sizeof(Point *));
    point->x = x;
    point->y = y;
    return point;
}