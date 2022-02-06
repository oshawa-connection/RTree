#include <stdio.h>
// #include "../headers/RTree.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "../headers/RTree.h"
#include <time.h>
#include <float.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

float randomf() {
    // float something = (float)(rand() % 100);
    float something = (float)rand();
    return something;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;
    const size_t NUMBER_OF_POINTS = 50;
    Point ** points = (Point **)malloc(sizeof(Point **) * NUMBER_OF_POINTS);
    RTreePtr rtree = createRTree();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        points[i] = createPoint(randomf(),randomf());
        // printf("Inserting point number %llu at: %f, %f\n",i,points[i]->x,points[i]->y);
        RTreeInsertPoint(rtree,points[i]);
    }

    FILE * outputfile = fopen("output/rtree.txt","w");
    serialiseRTree(rtree,outputfile);
    fclose(outputfile);
    start = clock();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        // printf("Finding point number %llu at: %f, %f\n",i,points[i]->x,points[i]->y);
        RTreeFindNearestNeighbour(rtree,points[i]);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using RTree\n",cpu_time_used);



    start = clock();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        Point * pointToFind = points[i];
        bool pointFound = false;
        for (uint64_t j = 0; j < NUMBER_OF_POINTS; j++) {
            Point * currentPoint = points[j];
            if (pointsAreEqual(pointToFind,currentPoint)) {
                pointFound = true;
                break;
            }
        }
        assert(pointFound == true);
        double currentMin = DBL_MAX;
        Point * bestPoint = NULL;
        for (uint64_t j = 0; j < NUMBER_OF_POINTS; j++) {
            Point * currentPoint = points[j];
            double currentDistance = distanceBetweenPoints(currentPoint,pointToFind);
            if (currentDistance < currentMin) {
                bestPoint = currentPoint;
                currentMin = currentDistance;
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using naive search\n",cpu_time_used);
    return EXIT_SUCCESS; 
}