#include "../headers/RTree.h"

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




/**
 * 
 * 
 * */
Node * _rTreeInsertPoint(RTree * rTree, Point * newPoint) {
    // Go from RootNode to leaf.
    //at each level, select the node, L, whose MBR will require the minimum area enlargement
    //to cover E.mbr
    printf("10\n");
    Node * currentNode = rTree->rootNode;
    Node * leafNode = _rTreeTraverseToLeaf(rTree,newPoint);
    printf("20\n");
    printf("leafnode MaxY is %f\n",leafNode->bbox->maxY);
    printf("leafnode MaxX is %f\n",leafNode->bbox->maxX);

    if (leafNode->nPoints + 1 < rTree->maxPointsPerNode) {
        int index = leafNode->nPoints + 1;
        printf("Leaf Node has %d points",leafNode->nPoints);
        leafNode->points[index] = newPoint;
        leafNode->nPoints ++;
    } else {
        printf("Performing split.");
    }
    printf("30\n");
    return leafNode;
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

