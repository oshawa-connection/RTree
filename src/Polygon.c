#include "../headers/Polygon.h"
#include <stdlib.h>

Polygon * createPolygon(Point * vertices) {
    Polygon * polygon = malloc(sizeof(Polygon));
    polygon->vertices=vertices;
    return polygon;
}


void deletePolygon(Polygon * polygon){

}

double getMaxd() {

}

double getMind() {

}