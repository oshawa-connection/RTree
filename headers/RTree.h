#include <stdio.h>
#include "BBox.h"
#include <float.h>

typedef enum {false=0, true=1} bool;


typedef struct Node {
    Point ** points;
    int nPoints;
    int nNodes;
    BBox * bbox;
    struct Node * nextNodes;
} Node;


typedef struct {
    int depth;
    int maxPointsPerNode;
    Node * rootNode; // does not store points! Only Bboxes!
    BBox * overallBbox;
} RTree;

/**
 * 
 * */
bool _nodeIsALeaf(Node * node) {
    if (node->nextNodes == NULL) {
        return true;
    }

    return false;
}

Node * _rTreeTraverseToLeaf(RTree * rTree, Point * point) {
    Node * currentNode = rTree->rootNode;
    
    while (!(_nodeIsALeaf(currentNode))) {
        float currentMin = FLT_MAX;
        Node * smallestEnlargementNode = NULL;
        for (int nNode = 0; nNode < currentNode->nNodes; nNode++) {
            Node * currentChild =  &(currentNode->nextNodes[nNode]);
            float enlargementArea = BboxMinEnlargementArea(currentChild->bbox,point);
            if (currentMin > enlargementArea) {
                currentMin = enlargementArea;
                smallestEnlargementNode = currentChild;
                
            }
        }

        currentNode = smallestEnlargementNode;  
    }
    
    return currentNode;
}

// typedef struct Node {
//     Point ** points;
//     int nPoints;
//     int nNodes;
//     BBox * bbox;
//     struct Node * nextNodes;
// } Node;



/**
 * 
 * */
void _rTreeInsertNode(RTree * rTree, Node * newNode) {
    // Go from RootNode to leaf.
    //at each level, select the node, L, whose MBR will require the minimum area enlargement
    //to cover E.mbr
    Node * currentNode = rTree->rootNode;
    // for(int i = 0;i < rTree->rootNode->nNodes; i++) {
    //     for (int j=0; j < 0;j++)
    // }
    
}


/**
 * 
 * */
void _rTreeSearch(RTree * rTree, Node * queryNode) {
    int numberOfChildNodes = rTree->rootNode->nNodes;
    for(int childNodeN =0; childNodeN < numberOfChildNodes;childNodeN ++) {
        
    }
}

