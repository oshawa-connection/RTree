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

static const double cluster1X = 1000.0;
static const double cluster1Y = 1000.0;

static const double cluster2X = 2000.0;
static const double cluster2Y = 2000.0;


Point * clusteredPoint() {
    bool coinFlip = rand() > RAND_MAX / 2;
    
    if (coinFlip == true) {
        return createPoint(cluster1X + (rand() % 50),cluster1Y + (rand() % 50));
    } else {
        return createPoint(cluster2X + (rand() % 50),cluster2Y + (rand() % 50));
    }
}


int main(int argc, char **argv) {
    // char * numberOfPoints = malloc(255 * sizeof(char));
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used_rtree;
    double cpu_time_used_naive;
    const size_t NUMBER_OF_POINTS = 5000;
    Point ** points = (Point **)malloc(sizeof(Point **) * NUMBER_OF_POINTS);
    RTreePtr rtree = createRTree();
    for(uint64_t i = 0;i < NUMBER_OF_POINTS; i++) {
        // points[i] = createPoint(randomf(),randomf());
        points[i] = clusteredPoint();
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
    cpu_time_used_rtree = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using RTree\n",cpu_time_used_rtree);



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
    cpu_time_used_naive = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds to find nearest neighbours using naive search\n",cpu_time_used_naive);
    double percentageDifference = (cpu_time_used_naive - cpu_time_used_rtree) / cpu_time_used_rtree * 100;
    printf("RTree was %f %% faster than the naive case\n",percentageDifference);

    return EXIT_SUCCESS; 
}