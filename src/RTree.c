#include "../headers/RTree.h"
#include <float.h>
#include "../headers/Node.h"
#include <stdlib.h>
#include "../headers/BBox.h"
#include <glib.h>

RTree * createRTree() {
    RTree * rtree = (RTree *)malloc(sizeof(RTree));
    BBox * bbox = createBBox(0,0.0,0.0,0.0,0.0);
    rtree->rootNode = createNode(bbox);
    return rtree;
}


NodePtr _rTreeTraverseToLeaf(RTree * rTree, Point * point) {
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
            }
        }
        // TODO: And enlargen the bbox if enlargementArea > 0 in insert 
        currentNode = smallestEnlargementNode;  
    }
    
    return currentNode;
}




/**
 * 
 * 
 * */
NodePtr _rTreeInsertPoint(RTree * rTree, Point * newPoint) {
    // Go from RootNode to leaf.
    //at each level, select the node, L, whose MBR will require the minimum area enlargement
    //to cover E.mbr
    
    // NodePtr currentNode = rTree->rootNode;
    // NodePtr leafNode = _rTreeTraverseToLeaf(rTree,newPoint);
    
    // printf("leafnode MaxY is %f\n",leafNode->bbox->maxY);
    // printf("leafnode MaxX is %f\n",leafNode->bbox->maxX);

    // if (leafNode->nPoints + 1 < rTree->maxPointsFORNode) {
    //     int index = leafNode->nPoints + 1;
    //     printf("Leaf Node has %d points",leafNode->nPoints);
    //     leafNode->points[index] = newPoint;
    //     leafNode->nPoints ++;
        
    // } else {
    //     printf("... so performing the split.\n");
    //     // Here, you have to split the leafNode.
    //     // Enlargen 
    //     // set to 0 and split the points in amongst the two new children
    //     leafNode->nPoints = 0;
        
    //     // Node rightTopLeaf = {NULL,5,0,&rightTopBbox,NULL};


    

    // }
    
    // // Enlargen bbox if necessary
    // // bboxEnlargen
    // // leafNode->bbox
    // return leafNode;
    return rTree->rootNode;
}


/**
 * 
 * */
void _rTreeSearch(RTree * rTree, NodePtr queryNode) {
    // int numberOfChildNodes = rTree->rootNode->nNodes;
    // for(int childNodeN =0; childNodeN < numberOfChildNodes;childNodeN ++) {
        
    // }
}

