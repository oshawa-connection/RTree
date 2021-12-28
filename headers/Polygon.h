#pragma once
#include "./Point.h"

typedef struct Polygon{
    Point * vertices;
} Polygon;


Polygon * createPolygon(Point * vertices);

void deletePolygon(Polygon * polygon);