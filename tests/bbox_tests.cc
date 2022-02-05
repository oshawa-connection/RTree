#include <gtest/gtest.h>
#include "../headers/BBox.h"
// #include "../src/Point.c"

// Demonstrate some basic assertions.
TEST(BBoxTest, CalculatesDistanceToVertex) {
    Point * point = createPoint(1,1);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(1.4142135624,result);
}


TEST(BBoxTest, CalculatesDistanceToPointWithinBBox) {
    Point * point = createPoint(3,3);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(0.0,result);
}


TEST(BBoxTest, CalculatesDistanceToLine) {
    Point * point = createPoint(3,0);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(2.0,result);
}

TEST(BBoxTest, CalculatateDistanceBottomLeft) {
    Point * point = createPoint(0,0);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(2.8284271,result);
}


TEST(BBoxTest, CalculateDistanceToPointWithinBBox) {
    Point * point = createPoint(3,3);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(0,result);
}

TEST(BBoxTest, CalculateDistanceToPointBelowBBox) {
    Point * point = createPoint(3,1);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(1,result);
}


TEST(BBoxTest, CalculateDistanceToPointRightOfBBox) {
    Point * point = createPoint(5,3);
    BBox * bbox = createBBox(0,2,2,4,4);
    double result = bboxDistanceToPoint(bbox,point);
    EXPECT_FLOAT_EQ(1,result);
}