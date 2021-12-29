#pragma once
#include <stdbool.h>

typedef struct Point{
    float x;
    float y;
} Point;

// Todo: switch to double.
Point * createPoint(float x, float y);

double distanceBetweenPoints(Point * point, Point * otherPoint);

bool pointsAreEqual(Point * point, Point * otherPoint);