#include <gtest/gtest.h>
// FIXME: Something isn't quite right with the CMakeLists file.
#include "../src/Node.c"
// #include "../headers/Node.h"
#include "../headers/BBox.h"

TEST(NodeTests, CanCreate) {
    BBox bbox = {1,1.0,1.0f,1.0,1.0};
    NodePtr someNode = createNode(&bbox);
    // NodePtr node =  createNode(&bbox);
    BBox * nodeBBox = getNodeBBox(someNode);
    EXPECT_EQ(nodeBBox->id,bbox.id);
    EXPECT_EQ(nodeBBox,&bbox);
}