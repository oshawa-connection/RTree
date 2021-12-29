#include <gtest/gtest.h>
#include "../headers/Point.h"

TEST(Point, CalculateDistanceBetweenPoints) {
    Point * pointOne = createPoint(0.0,0.0);
    Point * pointTwo = createPoint(2.2,0.0);
    double result = distanceBetweenPoints(pointOne,pointTwo);
    EXPECT_FLOAT_EQ(result,2.2);
}

TEST(Point, CalculateDistanceBetweenIdenticalPoints) {
    Point * pointOne = createPoint(0.0,0.0);
    Point * pointTwo = createPoint(0.0,0.0);
    double result = distanceBetweenPoints(pointOne,pointTwo);
    EXPECT_FLOAT_EQ(result,0.0);
}

TEST(Point, CalculateDistanceBetweenNegativePoints) {
    Point * pointOne = createPoint(-1.1,0.0);
    Point * pointTwo = createPoint(-2.2,0.0);
    double result = distanceBetweenPoints(pointOne,pointTwo);
    EXPECT_FLOAT_EQ(result,1.1);
}

// Now 
TEST(Point, CalculateDistanceBetweenNonOrthogonalPoints) {
    Point * pointOne = createPoint(1.0,2.0);
    Point * pointTwo = createPoint(0.0,0.0);
    double result = distanceBetweenPoints(pointOne,pointTwo);
    EXPECT_FLOAT_EQ(result,2.2360679775);
}



TEST(Point, pointsAreEqual) {
    Point * pointOne = createPoint(-1.1,0.0);
    Point * pointTwo = createPoint(-1.1,0.0);
    EXPECT_TRUE(pointsAreEqual(pointTwo,pointOne));
    // EXPECT_FLOAT_EQ(result,1.1);
}