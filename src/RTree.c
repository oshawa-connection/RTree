#include "../headers/RTree.h"
#include <float.h>
#include "../headers/Node.h"
#include <stdlib.h>
#include "../headers/BBox.h"
#include <glib.h>
#include "../headers/Node.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "../headers/PriorityQueue.h"

// Used to prevent infinite recursion
#define RTREE_MAX_DEPTH 100

typedef struct RTree {
    int depth;
    NodePtr rootNode; 
    GQueue* nodeQueue;
    PriorityQueuePtr priorityQueue;
} RTree;


RTreePtr createRTree() {
    RTreePtr rtree = (RTreePtr)malloc(sizeof(RTree));
    BBox * bbox = createBBox(0,0.0,0.0,0.0,0.0);
    
    rtree->rootNode = createNode(bbox);
    rtree->nodeQueue = g_queue_new();

    rtree->priorityQueue = NULL; // create a new one each time.
    return rtree;
}

/**
 * TODO: Run through the tree, freeing all child nodes too.
 * 
 * */
void deleteRTree(RTreePtr* rtree) {
    RTreePtr rtreePtr = *rtree;
    g_queue_free(rtreePtr->nodeQueue);
    free(*rtree);
    *rtree = NULL;
}

int getRTreeDepth(RTreePtr rtree) {
    return rtree->depth;
}

/** 
 * Add node to queue. This could either be for searching or enlargening.
 * TODO: We need some way to stop duplicate items being added.
 * This could be done using a tree https://docs.gtk.org/glib/method.Tree.lookup.html
 * acting as a form of "Set".
 * Lookup would be O(log n)
 * Insertion is _apparently_ O(log n)?
 * */
void addNodeToQueue(RTreePtr rtree, NodePtr nodeToAdd) {
    g_queue_push_head(rtree->nodeQueue,nodeToAdd);
    // NodePtr myX = (NodePtr)g_queue_pop_head(myQueue);
}


NodePtr getNextNodeFromQueue(RTreePtr rTree) {
    NodePtr currentNode = (NodePtr)g_queue_pop_head(rTree->nodeQueue);
}

/**
 * Go from RootNode to leaf.
 * At each level, select the node, L, whose MBR will require the minimum area enlargement
 * to cover E.mbr.
 * At each level, there is only one best candidate.
 * */
NodePtr _rTreeTraverseToLeafEnlargen(RTreePtr rTree, Point * point) {
    NodePtr currentNode = rTree->rootNode;
    
    while (!(nodeIsLeaf(currentNode))) {
        float currentMin = FLT_MAX;
        NodePtr smallestEnlargementNode = NULL;
        int nodeCount = 0;
        NodePtr currentChild = NULL;
        while((currentChild = getChildNodeAt(currentNode,nodeCount++))) {
            float enlargementArea = BboxMinEnlargementArea(getNodeBBox(currentChild),point);
            if (currentMin > enlargementArea) {
                currentMin = enlargementArea;
                smallestEnlargementNode = currentChild;
                addNodeToQueue(rTree,currentChild);
            }
        }
        currentNode = smallestEnlargementNode;  
    }
    
    return currentNode;
}


void _enlargenAllNodes(RTreePtr rTree, Point * newPoint) {
    NodePtr currentNode = NULL;
    while ((currentNode = (NodePtr) g_queue_pop_head(rTree->nodeQueue))) {
        BBox * bbox = getNodeBBox(currentNode);
        BboxEnlargen(bbox,newPoint);
    }
    assert(g_queue_get_length(rTree->nodeQueue) == 0);
}

/**
 * 
 * 
 * */
void RTreeInsertPoint(RTreePtr rTree, Point * newPoint) {
    //g_queue_clear(rTree->nodeQueue);
    
    NodePtr bestNode = _rTreeTraverseToLeafEnlargen(rTree,newPoint);
    if(addPointToNode(bestNode,newPoint) == false) {
        rTree->depth += 1;
        if (rTree->depth > RTREE_MAX_DEPTH) {
            fprintf(stderr,"RTree is exceeding maximum depth, exiting\n");
            exit(1);
        }
        if(splitNode(bestNode) == false) {
            exit(1);
        } else {
            return RTreeInsertPoint(rTree, newPoint);
        }
    }
    printf("LENGTH OF QUEUE IS %d\n",g_queue_get_length(rTree->nodeQueue));
    _enlargenAllNodes(rTree,newPoint);
}


void findLeavesWithinDistance(RTreePtr rTree, Point * queryPoint, double distanceLimit) {
    assert(g_queue_is_empty(rTree->nodeQueue) == true);

    addNodeToQueue(rTree,rTree->rootNode);
    // if the node is within the specified distance 
        // if it is a leaf
            //add it to the priority queue
        // else 
            // add its children to the regular node queue.
    NodePtr currentNode = NULL;
    while((currentNode = getNextNodeFromQueue(rTree))) {
        nodeWithinDistance(currentNode,queryPoint,distanceLimit);
    }

    // getNextNodeFromQueue
    // if (nodeWithinDistance())
}

/**
 * 
 * */
NodePtr _rTreeSearch(RTreePtr rTree, Point * queryPoint) {
    assert(pqIsEmpty(&rTree->priorityQueue) == true);
    NodePtr rootNode = rTree->rootNode;
    if (!RTreecontainsPoint(rTree,queryPoint)) {
        fprintf(stdout, "Query point does not exist in RTree");
        return NULL;
    }

    
    // Set with initial priority of zero as there will only be one element.
    pqPush(&rTree->priorityQueue,rTree->rootNode,0.0);
    /** 
     * TODO: this initial search distance could be calculated to a reasonable 
     * initial guess based on the dimensions of the root node?
     * */
    findLeavesWithinDistance(rTree,queryPoint,5.0); //TODO: then add them to priority queue.
    uint64_t length = 0;
    
    if (length == 0) {
        // Then try again with a larger distance, up to a maximum number of tries / distance based on rootnode.
    }
    while(!pqIsEmpty(&rTree->priorityQueue)) {
        NodePtr currentNode = pqPeek(&rTree->priorityQueue);
        Point * point = getPointAt(currentNode, 0);
        double currentBestDistance = distanceBetweenPoints(point,queryPoint);
        double nextNearestBBox = pqPeekPriority(&rTree->priorityQueue);
        if (currentBestDistance > nextNearestBBox) {
            //TODO: then continue searching.
        } else {
            return currentNode;
        }

    }
    return NULL;
}

/**
 * Nodes can potentially overlap, therefore it is not a simple case of just 
 * navigating down to the single leaf node. All candidate leaves must be investigated.
 * TODO: switch to using a priority queue. 
 * TODO: try to get bboxes to overlap.
 * */
bool RTreecontainsPoint(RTreePtr rTree, Point * point) {
    assert(g_queue_is_empty(rTree->nodeQueue) == true);
    addNodeToQueue(rTree,rTree->rootNode);
    while(!g_queue_is_empty(rTree->nodeQueue)) {
        NodePtr currentNode = getNextNodeFromQueue(rTree);
        // If the node is a leaf, just search the points 
        if (nodeIsLeaf(currentNode)) {
            if (nodeContainsPoint(currentNode,point)) {
                // exit early, clearing queue as we don't need it anymore.
                //TODO: wrap in function.
                g_queue_clear(rTree->nodeQueue);
                return true;
            }
        } else { 
            // else check its children.
            size_t nodeCount = 0;
            NodePtr currentChild = NULL;
            while((currentChild = getChildNodeAt(currentNode,nodeCount++))) {
                if (nodeEnclosesPoint(currentChild,point)) {
                    addNodeToQueue(rTree,currentChild);
                }
            }
        }
    }
    return false;
}

