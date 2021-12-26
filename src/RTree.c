#include "../headers/RTree.h"
#include <float.h>
#include "../headers/Node.h"
#include <stdlib.h>
#include "../headers/BBox.h"
#include <glib.h>
#include "../headers/Node.h"
#include <stdbool.h>
#include <stdio.h>

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

void addNodeToEnlargenQueue(RTreePtr rtree, NodePtr nodeToAdd) {
    g_queue_push_head(rtree->nodeQueue,nodeToAdd);
    // NodePtr myX = (NodePtr)g_queue_pop_head(myQueue);
}


// Go from RootNode to leaf.
//at each level, select the node, L, whose MBR will require the minimum area enlargement
//to cover E.mbr
NodePtr _rTreeTraverseToLeaf(RTreePtr rTree, Point * point) {
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
                addNodeToEnlargenQueue(rTree,currentChild);
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
    
}

/**
 * 
 * 
 * */
void RTreeInsertPoint(RTreePtr rTree, Point * newPoint) {
    g_queue_clear(rTree->nodeQueue);
    
    NodePtr bestNode = _rTreeTraverseToLeaf(rTree,newPoint);
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

