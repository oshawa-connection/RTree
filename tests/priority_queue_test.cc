#include <gtest/gtest.h>
//EVIL!!! 
#include "../src/PriorityQueue.c"
#include "../headers/Node.h"
#include "../headers/BBox.h"

TEST(PriorityQueue,CalculatesLengthCorrectly) {
    PriorityQueuePtr pq = NULL;
    BBox * bbox = createBBox(0,1,2,3,4);
    NodePtr node = createNode(bbox);
    NodePtr node2 = createNode(bbox);
    // doNothing();
    pqPush(&pq,node,2.0);
    pqPush(&pq,node2,3.0);
    uint64_t length =  pqGetLength(&pq);
    EXPECT_EQ(length,2);
}

TEST(PriorityQueue,CalculatesEmptyLengthCorrectly) {
    PriorityQueuePtr pq = NULL;    
    // pqPush(&pq,node,2.0);
    // pqPush(&pq,node2,3.0);
    uint64_t length =  pqGetLength(&pq);
    EXPECT_EQ(length,0);
}


TEST(PriorityQueue,CalculatesRemovedLengthCorrectly) {
    PriorityQueuePtr pq = NULL;    
    BBox * bbox = createBBox(0,1,2,3,4);
    NodePtr node = createNode(bbox);
    NodePtr node2 = createNode(bbox);
    pqPush(&pq,node,2.0);
    pqPush(&pq,node2,3.0);
    pqPop(&pq);
    uint64_t length =  pqGetLength(&pq);
    EXPECT_EQ(length,1);
}