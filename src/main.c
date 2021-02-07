#include <stdio.h>
#include "../headers/RTree.h"
#include <math.h>
#include <string.h>

const float floatTol = 0.001;

void fAssertEqual(float expected, float actual, float tolerance) {
    float difference = fabs(expected - actual);
    
    if (!(difference < tolerance)) {
        printf("Assertation failed. Expected %f to equal %f.",expected, actual);
    }
}

void AssertTrue(bool value) {
    if (!value) {
        printf("Assertation failed. Expected true but got false");
    }
}

void test__rTreeTraverseToLeaf() {
    BBox bboxLeftNode = {1,1,1.5,1.5};
    Node leftNode = {NULL,0,0,&bboxLeftNode,NULL};

    BBox bboxRightNode = {1.5,1.5,2,2};
    Node rightNode = {NULL,0,0,&bboxRightNode,NULL};
    Node nextNodes[] = {leftNode,rightNode};
    Node rootNode = {NULL,10,2,NULL,&nextNodes};
    RTree rTree = {1,5,&rootNode,NULL};

    Point myPoint = {1.25,1.25};
    Node * foundNode = _rTreeTraverseToLeaf(&rTree, &myPoint);
    
    fAssertEqual(bboxLeftNode.maxX,foundNode->bbox->maxX,floatTol);
}

void testSuite() {

    
    
    Node rootNode = {0,NULL,NULL};
    if (!_nodeIsALeaf(&rootNode)) {
        printf("Error\n");
    }

    /**
     * Test BBox
     * */
    BBox myFirstBbox = {1.0,1.0,3.0,3.0};
    Point outOfBoundsPoint = {4.0,4.0};
    float newArea = BboxMinEnlargementArea(&myFirstBbox,&outOfBoundsPoint);
    fAssertEqual(5,newArea,floatTol);
    Point inBoundsPoint = {1.5,1.5};
    newArea = BboxMinEnlargementArea(&myFirstBbox,&inBoundsPoint);
    fAssertEqual(0.0,newArea,floatTol);

    test__rTreeTraverseToLeaf();
    /**
     * 
     * */
}


int main(int argc, char **argv) {
    
    if (argc > 1) {
        char testOption[] = "-test";
        for (int i = 0; i < argc; ++i) {
    
            if (strcmp(argv[i], testOption)) {
                testSuite();
                // fflush(stdout);
                // fflush(stderr);
                printf("All tests completed");
                // return 0;
            }
        }
    } 

    

    // printf("Hello world\n");
}