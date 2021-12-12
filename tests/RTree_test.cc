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
    
    deleteRTree(&rtree);
    // free(pointToInsert);
}