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

TEST(RTreeTests, CanInsertWithASplit) {
    RTreePtr rtree = createRTree();
    for(int i =0; i<100;i++) {
        //Memory leak but I don't care
        Point * pointToInsert = createPoint(1.0,(float)i);
        RTreeInsertPoint(rtree,pointToInsert);
    }
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

