#include <gtest/gtest.h>
#include "../src/RTree.c"


TEST(RTreeTests, CanCreate) {
    RTreePtr rtree = createRTree();
    deleteRTree(&rtree);
    
}

TEST(RTreeTests, CanInsertWithoutSplit) {
    RTreePtr rtree = createRTree();
    Point * pointToInsert = createPoint(1.0,1.0);
    RTreeInsertPoint(rtree,pointToInsert);
    deleteRTree(&rtree);
    free(pointToInsert);
}

/**
 * RTreeTests.CanInsertWithASplit sometimes gives a "RTree is exceeding maximum depth, exiting"
 * Could this be something to do with floating point precision?
 * 
 * */
TEST(RTreeTests, CanInsertWithASplit) {
    RTreePtr rtree = createRTree();
    for(int i =0; i<100;i++) {
        //Memory leak but I don't care
        Point * pointToInsert = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
    BBox * rootBBox = getNodeBBox(rtree->rootNode);
    EXPECT_FLOAT_EQ(rootBBox->maxX,(double)99);
    EXPECT_FLOAT_EQ(rootBBox->minX,(double)0);
    EXPECT_FLOAT_EQ(rootBBox->maxY,(double)99);
    // Point * pointToInsert = createPoint(1.0,1.0);
    int depth = getRTreeDepth(rtree);
    printf("Depth of RTree is: %d\n",depth);
    deleteRTree(&rtree);
    // TODO: ensure that all parent bboxes are larger than child bboxes.
    // free(pointToInsert);
}

TEST(RTreeTests, CanFindPoint) {
    RTreePtr rtree = createRTree();
    Point * pointToInsert;
    for(int i =0; i<100;i++) {
        //Memory leak but I don't care
        pointToInsert = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
    bool result = RTreecontainsPoint(rtree,pointToInsert);
    Point * point = createPoint(50.0,50.0);
    bool otherresult = RTreecontainsPoint(rtree,point);
    EXPECT_TRUE(result);
    EXPECT_TRUE(otherresult);
}

// TODO: this sometimes results in a (Address boundary error), but not always..
TEST(RTreeTests, CanSearchForNearestNeighbour) {
    RTreePtr rtree = createRTree();
    Point * pointToInsert;
    for(int i =0; i<100;i++) {
        //Memory leak but I don't care
        pointToInsert = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
    Point * nearestPoint = RTreeFindNearestNeighbour(rtree, pointToInsert);
    EXPECT_FLOAT_EQ(nearestPoint->x,(float)98);
    EXPECT_FLOAT_EQ(nearestPoint->x,(float)98);
}

TEST(RTreeTests, CanInsertLotsOfPoints) {
    RTreePtr rtree = createRTree();
    Point * pointToInsert;
    for(int i =0; i<1000;i++) {
        //Memory leak but I don't care
        pointToInsert = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
}

TEST(RTreeTests,CanSearchMultipleTimes) {
    RTreePtr rtree = createRTree();
    Point * pointToInsert;
    for(int i =0; i<100;i++) {
        //Memory leak but I don't care
        pointToInsert = createPoint((float)i,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
    Point * nearestPoint = RTreeFindNearestNeighbour(rtree, pointToInsert);
    Point * nearestPointTwo = RTreeFindNearestNeighbour(rtree, pointToInsert);
    EXPECT_FLOAT_EQ(nearestPoint->x,(float)98);
    EXPECT_FLOAT_EQ(nearestPoint->x,(float)98);
}