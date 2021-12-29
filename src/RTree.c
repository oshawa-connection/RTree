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

// Used to prevent infinite recursion
#define RTREE_MAX_DEPTH 100

typedef struct RTree {
    int depth;
    NodePtr rootNode; 
    GQueue* nodeQueue;
} RTree;


RTreePtr createRTree() {
    RTreePtr rtree = (RTreePtr)malloc(sizeof(RTree));
    BBox * bbox = createBBox(0,0.0,0.0,0.0,0.0);
    
    rtree->rootNode = createNode(bbox);
    rtree->nodeQueue = g_queue_new();
    
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
    //Now enlargen all in the queue, including the root node.
}


/**
 * 
 * */
void _rTreeSearch(RTreePtr rTree, NodePtr queryNode) {
    // int numberOfChildNodes = rTree->rootNode->nNodes;
    // for(int childNodeN =0; childNodeN < numberOfChildNodes;childNodeN ++) {
        
    // }
}

void _rtreeTraverseToLeafContains() {

}


bool RTreecontainsPoint(RTreePtr rTree, Point * point) {
    assert(g_queue_is_empty(rTree->nodeQueue) == true);
    addNodeToQueue(rTree,rTree->rootNode);
    while(!g_queue_is_empty(rTree->nodeQueue)) {
        // Todo: This should be wrapped up in a function.
        NodePtr currentNode = (NodePtr)g_queue_pop_head(rTree->nodeQueue);
        // If the node is a leaf, just search the points 
        if (nodeIsLeaf(currentNode)) {
            
            if (nodeContainsPoint(currentNode,point)) {
                
            }
            
        } else { 
            // else check its children.
            int nodeCount = 0;
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