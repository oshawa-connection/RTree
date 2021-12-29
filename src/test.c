// #include <stdio.h>
// #include "../headers/testUtils.h"
// #include "../headers/types.h"
// #include "../headers/RTree.h"
// #include <math.h>

// const float floatTol = 0.001;

// static void iAssertEqual(int expected, int actual, char * message) {
//     if (!(expected == actual)) {
//         printf("Assertation failed: %s; Expected %d to equal %d.\n",message,expected, actual);
//     }
// }

// static void fAssertEqual(float expected, float actual, float tolerance, char * message) {
//     float difference = fabs(expected - actual);
    
//     if (!(difference < tolerance)) {
//         printf("Assertation failed: %s; Expected %f to equal %f.\n",message,expected, actual);
//     }
// }

// static void AssertTrue(bool value) {
//     if (!value) {
//         printf("Assertation failed. Expected true but got false\n");
//     }
// }

// void test__rTreeTraverseToLeaf() {
//     BBox bboxLeftNode = {11,1,1,1.5,1.5};
//     Node leftNode = {NULL,0,0,&bboxLeftNode,NULL};

//     BBox bboxRightNode = {22,1.5,1.5,2,2};
//     BBox rightTopBbox = {33,1,1.5,1.5,3};
//     BBox rightBottomBbox = {44,1,1,1.5,1.5};

//     Node rightTopLeaf = {NULL,5,0,&rightTopBbox,NULL};
//     Node rightBottomLeaf = {NULL,5,0,&rightBottomBbox,NULL};

//     Node rightNodeChildren[] = {rightTopLeaf,rightBottomLeaf};
//     Node rightNode = {NULL,0,2,&bboxRightNode,&rightNodeChildren};

//     Node nextNodes[] = {leftNode,rightNode};
//     Node rootNode = {NULL,10,2,NULL,&nextNodes};
//     RTree rTree = {1,5,&rootNode,NULL};

//     Point myPoint = {1.25,1.25};
//     Node * foundNode = _rTreeTraverseToLeafEnlargen(&rTree, &myPoint);
    
//     char str[] = "My message here";

//     fAssertEqual(rightBottomBbox.maxX,foundNode->bbox->maxX,floatTol,str);
// }

// void test__rTreeInsertPoint() {
    
//     BBox bboxLeftNode = {1,1.0,1.0,1.5,1.5};
//     Node leftNode = {NULL,0,0,&bboxLeftNode,NULL};

//     BBox bboxRightNode = {2,1.5,1.5,2,2};
//     BBox rightTopBbox = {3,1,1.5,1.5,3};
//     BBox rightBottomBbox = {4,1,1,1.5,1.5};
    
//     Node rightTopLeaf = {NULL,5,0,&rightTopBbox,NULL};
//     Point rightBottomPoints[5] = {{1.1,1.1},{1.1,1.1},{1.1,1.1}};
//     Node rightBottomLeaf = {&rightBottomPoints,3,0,&rightBottomBbox,NULL};

//     Node rightNodeChildren[] = {rightTopLeaf,rightBottomLeaf};
//     Node rightNode = {NULL,0,2,&bboxRightNode,&rightNodeChildren};

//     Node nextNodes[] = {leftNode,rightNode};
//     Node rootNode = {NULL,10,2,NULL,&nextNodes};
//     RTree rTree = {1,5,&rootNode,NULL};
    

//     Point myPoint = {1.25,1.25};
    
//     Node * editedLeaf = _rTreeInsertPoint(&rTree,&myPoint);
    
//     char str[] = "never"; 
    
//     iAssertEqual(rightBottomLeaf.nPoints +1,editedLeaf->nPoints,str);
// }

// void testSuite() {

//     Node rootNode = {0,NULL,NULL};
//     if (!_nodeIsALeaf(&rootNode)) {
//         printf("Error\n");
//     }

//     /**
//      * Test BBox
//      * */
//     BBox myFirstBbox = {1,1.0,1.0,3.0,3.0};
//     Point outOfBoundsPoint = {4.0,4.0};
//     float newArea = BboxMinEnlargementArea(&myFirstBbox,&outOfBoundsPoint);
    
//     char someMessage[] = "New Area should be calculated correctly\n";
//     // 9 - 4 = 5
//     fAssertEqual(5,newArea,floatTol,someMessage);


//     Point inBoundsPoint = {1.5,1.5};
//     newArea = BboxMinEnlargementArea(&myFirstBbox,&inBoundsPoint);
//     char someOtherMessage[] = "Press E to pay respects\n";
    
//     // No new area to add so 0
//     fAssertEqual(0,newArea,floatTol,someOtherMessage);
    
//     // test__rTreeTraverseToLeaf();
//     test__rTreeInsertPoint();

// }


