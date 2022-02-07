#include <stdlib.h>
#include <gtest/gtest.h>
// FIXME: Something isn't quite right with the CMakeLists file.
#include "../src/Node.c"
#include "../headers/Point.h"
// #include "../headers/Node.h"
#include "../src/BBox.c"
#include "../src/Point.c"



TEST(NodeTests, CanCreateAndDestroy) {
    BBox bbox = {1,1.0,1.0f,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    // NodePtr node =  createNode(&bbox);
    BBox * nodeBBox = getNodeBBox(someNode);
    EXPECT_EQ(nodeBBox->id,bbox.id);
    EXPECT_EQ(nodeBBox,&bbox);
    free(someNode);
}


TEST(NodeTests,IsLeafWhenLeaf) {
    BBox bbox = {1,1.0,1.0f,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    bool result = nodeIsLeaf(someNode);
    EXPECT_TRUE(result);
    free(someNode);
}


TEST(NodeTests,DeterminesIfNotLeaf) {
    BBox bbox = {1,1.0,1.0,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    Point somePoint = {1.0f,2.0f};
    addPointToNode(someNode, &somePoint);
    bool result = nodeIsLeaf(someNode);
    EXPECT_FALSE(result);
    free(someNode);
}

TEST(NodeTests, CanAddPoint) {
    
    BBox bbox = {1,1.0,1.0,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    Point somePoint = {1.0f,2.0f};
    bool result = addPointToNode(someNode, &somePoint);
    
    EXPECT_TRUE(result);
    // This might cause a crash because when we free a stack allocated variable (bbox), it might not like it.
    // TODO: malloc bbox instead.
    free(someNode);
}

TEST(NodeTests, TellsWhenToSplitNode) {
    BBox bbox = {1,1.0,1.0,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    Point somePoint = {1.0f,2.0f};
    bool result = true;
    for(int i =0; i < MAX_POINTS_PER_NODE +1;i ++) {
        result = addPointToNode(someNode, &somePoint);
    }

    EXPECT_FALSE(result);
    free(someNode);
}


TEST(NodeTests,SplitsCorrectly) {
    // TODO: Once we set up bbox enlargen, this will not work. We also need to allow node to free the bbox.
    BBox * bbox = createBBox(1,1.0,1.0,1.0,1.0);
    NodePtr someNode = createNode(bbox);
    Point somePoint = {1.0f,2.0f};
    
    bool result = true;
    //Varience is in Y, so we expect the split to be along the Y axis in order
    //to split that in half
    for(int i =0; i < 5;i ++) {
        // memory leak
        Point * point = createPoint((float)i,(float)i);
        // We overload the node so that it is ready to split.
        result = addPointToNode(someNode, point);
    }

    bool splitResult = splitNode(someNode);
    //True if success, false if there was an error.
    EXPECT_TRUE(splitResult);
    //We expect the split node (which is now a parent, not a leaf)
    // to have 0 points itself.
    EXPECT_EQ(someNode->nPoints,0);
    // we expect the split node to now have 2 children.
    EXPECT_EQ(someNode->nNodes,2);
    EXPECT_NE(someNode->nextNodes, (Node **) NULL);
    
    Node * leftNode = someNode->nextNodes[0];
    Node * rightNode = someNode->nextNodes[1];
    
    //mx,My     Mx,My
    // x ------ x
    // |        |
    // |        |
    // x ------ x Mx, my
    //mx,my
    // TODO: Once we set up bbox enlargen, this will not work. We also need to allow node to free the bbox.
    EXPECT_EQ(leftNode->nPoints,3);
    EXPECT_FLOAT_EQ(leftNode->bbox->minX,0);
    EXPECT_FLOAT_EQ(leftNode->bbox->maxX,2.0);
    EXPECT_FLOAT_EQ(leftNode->bbox->minY,0);
    EXPECT_FLOAT_EQ(leftNode->bbox->maxY,2);


    EXPECT_EQ(rightNode->nPoints,2);
    EXPECT_FLOAT_EQ(rightNode->bbox->minX,3.0);
    EXPECT_FLOAT_EQ(rightNode->bbox->maxX,4.0);
    EXPECT_FLOAT_EQ(rightNode->bbox->minY,3.0);
    EXPECT_FLOAT_EQ(rightNode->bbox->maxY,4.0);
}


TEST(NodeTests,SplitsCorrectly2) {
    // TODO: Once we set up bbox enlargen, this will not work. We also need to allow node to free the bbox.
    BBox * bbox = createBBox(1,1.0,1.0,1.0,1.0);
    NodePtr someNode = createNode(bbox);

    Point * point1 = createPoint(1000,1000);
    Point * point2 = createPoint(1001,1001);
    Point * point3 = createPoint(1002,1002);
    Point * point4 = createPoint(2000,2000);
    Point * point5 = createPoint(2001,2001);
    Point * point6 = createPoint(2002,2002);


    addPointToNode(someNode,point1);
    addPointToNode(someNode,point2);
    addPointToNode(someNode,point3);
    addPointToNode(someNode,point4);
    addPointToNode(someNode,point5);
    addPointToNode(someNode,point6);
    


    bool splitResult = splitNode(someNode);
    //True if success, false if there was an error.
    EXPECT_TRUE(splitResult);
    //We expect the split node (which is now a parent, not a leaf)
    // to have 0 points itself.
    EXPECT_EQ(someNode->nPoints,0);
    // we expect the split node to now have 2 children.
    EXPECT_EQ(someNode->nNodes,2);
    EXPECT_NE(someNode->nextNodes, (Node **) NULL);
    
    Node * leftNode = someNode->nextNodes[0];
    Node * rightNode = someNode->nextNodes[1];
    
    //mx,My     Mx,My
    // x ------ x
    // |        |
    // |        |
    // x ------ x Mx, my
    //mx,my
    // TODO: Once we set up bbox enlargen, this will not work. We also need to allow node to free the bbox.
    EXPECT_EQ(leftNode->nPoints,3);
    EXPECT_FLOAT_EQ(leftNode->bbox->minX,1000);
    EXPECT_FLOAT_EQ(leftNode->bbox->maxX,1002);
    EXPECT_FLOAT_EQ(leftNode->bbox->minY,1000);
    EXPECT_FLOAT_EQ(leftNode->bbox->maxY,1002);


    EXPECT_EQ(rightNode->nPoints,3);
    EXPECT_FLOAT_EQ(rightNode->bbox->minX,2000);
    EXPECT_FLOAT_EQ(rightNode->bbox->maxX,2002);
    EXPECT_FLOAT_EQ(rightNode->bbox->minY,2000);
    EXPECT_FLOAT_EQ(rightNode->bbox->maxY,2002);

    leftNode->bbox->id = 1;
    rightNode->bbox->id = 2;

    FILE * outputfile = fopen("output/rtree.txt","w");

    serialiseBBox(outputfile,rightNode->bbox);
    serialiseBBox(outputfile,leftNode->bbox);
    serialisePoint(point1,1,outputfile);
    serialisePoint(point2,1,outputfile);
    serialisePoint(point3,1,outputfile);
    serialisePoint(point4,2,outputfile);
    serialisePoint(point5,2,outputfile);
    serialisePoint(point6,2,outputfile);
    fclose(outputfile);

}



TEST(NodeTests,CanGetPointAt) {
    BBox * bbox = createBBox(0,0,1,0,1);
    NodePtr node = createNode(bbox);
    Point * firstPoint = createPoint(1,1);
    addPointToNode(node,firstPoint);
    Point * result = getPointAt(node,0);
    Point * resulttwo = getPointAt(node,1);
    EXPECT_NE(result,(Point *)NULL);
    EXPECT_EQ(resulttwo, (Point * ) NULL);
}

TEST(NodeTests,NodeContainsPoint) {
    Point * myPoint = createPoint(1.79,1.9137);
    BBox * bbox = createBBox(0,1.14559632,2.19,2.03,1.91);
    bool result = BBoxContainsPoint(bbox,myPoint);
    EXPECT_TRUE(result);
}