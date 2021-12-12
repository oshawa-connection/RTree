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
    for(int i =0; i < MAX_POINTS_PER_NODE +5;i ++) {
        // memory leak
        Point * point = createPoint(1,(float)i);
        result = addPointToNode(someNode, point);
    }

    NodeSplitResult * splitResult = splitNode(&someNode);
    EXPECT_FALSE(splitResult->error);
    EXPECT_NE(splitResult->leftNode,(Node *)NULL);
    EXPECT_NE(splitResult->rightNode,(Node * )NULL);
    // Could also use EXPECT_NEAR here.


    // expect it to free the node and set it to NULL;
    EXPECT_EQ(someNode, (Node * ) NULL);

    //mx,My     Mx,My
    // x ------ x
    // |        |
    // |        |
    // x ------ x Mx, my
    //mx,my
    // TODO: Once we set up bbox enlargen, this will not work. We also need to allow node to free the bbox.
    EXPECT_FLOAT_EQ(splitResult->leftNode->bbox->minX,bbox->minX);
    EXPECT_FLOAT_EQ(splitResult->leftNode->bbox->maxX,bbox->maxX);
    
    //Expect that the left and right bbox will have the same maxX (left) and minX (right)
    EXPECT_FLOAT_EQ(splitResult->leftNode->bbox->maxY,splitResult->rightNode->bbox->minY);
    // Expec that the number of points in each node is roughly equal.
    EXPECT_NEAR(splitResult->leftNode->nPoints,splitResult->rightNode->nPoints,2);
}