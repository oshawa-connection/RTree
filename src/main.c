#include <stdio.h>
// #include "../headers/RTree.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "../headers/RTree.h"
#include <time.h>

int main(int argc, char **argv) {
    clock_t start, end;
    double cpu_time_used;
    const size_t NUMBER_OF_POINTS = 10000;
    Point ** points = (Point **)malloc(sizeof(Point **) * NUMBER_OF_POINTS);
    RTreePtr rtree = createRTree();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        points[i] = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,points[i]);
    }

    start = clock();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        RTreeFindNearestNeighbour(rtree,points[i]);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using RTree\n",cpu_time_used);
    
    start = clock();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        Point * pointToFind = points[i];
        for (uint64_t j = 0; j < NUMBER_OF_POINTS; j++) {
            Point * currentPoint = points[j];
            if (pointsAreEqual(pointToFind,currentPoint)) {
                break;
            }
        }
        // RTreeFindNearestNeighbour(rtree,points[i]);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using naive search\n",cpu_time_used);
    return EXIT_SUCCESS; 
}