#include <stdlib.h>
#include <gtest/gtest.h>
// FIXME: Something isn't quite right with the CMakeLists file.
#include "../src/Node.c"
#include "../headers/Point.h"
// #include "../headers/Node.h"
#include "../headers/BBox.h"

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
    // TODO: malloc bbox here.
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