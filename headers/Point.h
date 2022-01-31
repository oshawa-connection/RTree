#pragma once
#include <stdbool.h>
#include <stdio.h>
typedef struct Point{
    double x;
    double y;
} Point;

// Todo: switch to double.
Point * createPoint(float x, float y);

double distanceBetweenPoints(Point * point, Point * otherPoint);

bool pointsAreEqual(Point * point, Point * otherPoint);

void serialisePoint(Point * point, int bboxID,  FILE * outputfile);