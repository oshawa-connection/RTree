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
    EXPECT_FLOAT_EQ(leftNode->bbox->minX,bbox->minX);
    EXPECT_FLOAT_EQ(leftNode->bbox->maxX,bbox->maxX);
    
    //Expect that the left and right bbox will have the same maxX (left) and minX (right)
    EXPECT_FLOAT_EQ(leftNode->bbox->maxY,rightNode->bbox->minY);
    // Expec that the number of points in each node is roughly equal.
    EXPECT_NEAR(leftNode->nPoints,rightNode->nPoints,2);
    // The sum of both should be the original number of points.
    EXPECT_EQ(leftNode->nPoints + rightNode->nPoints,MAX_POINTS_PER_NODE);
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