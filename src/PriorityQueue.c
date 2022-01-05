// C code to implement Priority Queue
// using Linked List
#include "../headers/PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
// #include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/Node.h"
// Node
typedef struct PQNode {
	// TODO: consider making this void * 
    NodePtr data;
 
    // Lower values indicate higher priority
    double priority;
 
    struct PQNode* next;
 
} PQNode;

// Function to Create A New Node
PriorityQueuePtr createPriorityQueue(NodePtr d, double p) {
    PriorityQueuePtr temp = (PriorityQueuePtr)malloc(sizeof(PQNode));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
double pqPeekPriority(PQNode** head) {
    return (*head)->priority;
}

// Return the value at head
NodePtr pqPeek(PQNode** head) {
    return (*head)->data;
}
 
// Removes the element with the
// highest priority form the list
void pqPop(PQNode** head) {
    PQNode* temp = *head;
    (*head) = (*head)->next;
    free(temp);
	temp = NULL;
}
 
// Function to push according to priority
void pqPush(PQNode** head, NodePtr dataValue, double priority) {
	// Special case when pushing to empty queue.
	if (*head == NULL) {
        // This might be slow. We can write a better implementation.
		*head = createPriorityQueue(dataValue, priority);
		return;
	}
    PQNode* start = (*head);
 
    // Create new PQNode
    PQNode* temp = createPriorityQueue(dataValue, priority);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > priority) {
 
        // Insert New PQNode before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->priority < priority) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
// Function to check is list is empty
bool pqIsEmpty(PQNode** head) {
    return (*head) == NULL;
}


void pqClear(PQNode** head) {
    while (!pqIsEmpty(head)) {
        pqPop(head);
    }
}


uint64_t pqGetLength(PQNode** head) {
    if (*head == NULL) {
        return 0;
    }
    uint64_t length = 1;
    PQNode* currentNode = (*head)->next;
    while(currentNode != NULL) {
        currentNode = currentNode->next;
        length += 1;
    }
    return length;
}


void doNothing() {

}
// // // Driver code
// int main()
// {
// 	PQNode* pq = createPriorityQueue(1, 1);
// 	char * inputString = malloc(255 * sizeof(char));
// 	while(1) {
// 		printf(">");
// 		fgets(inputString, 255, stdin);
// 		if (strcmp(inputString,"peek\n") == 0) {
// 			if (pqIsEmpty(&pq)) {
// 				printf("Priority queue is empty\n");
// 			} else 
// 			{
// 				printf("%f\n",pqPeek(&pq));				
// 			}

// 		}
// 		if (strcmp(inputString,"pop\n") == 0) {
// 			if (pqIsEmpty(&pq)) {
// 				printf("Could not pop, queue is empty.\n");
// 			} else {
// 				double oldHead = pqPeek(&pq);
// 				pqPop(&pq);
// 				if (pqIsEmpty(&pq)) {
// 					printf("popped %.2f. Priority Queue is now empty.\n",oldHead);
// 				} else {
// 					printf("popped %.2f Head is now: %.2f\n",oldHead,pqPeek(&pq));
// 				}
// 			}
// 		}

// 		if (strncmp(inputString,"push",4) == 0) {
// 			double value;
// 			char str[20];
// 			sscanf(inputString,"%s%lf",str,&value);
			
// 			pqPush(&pq,value,value);
// 			double currentHead = pqPeek(&pq);
// 			printf("Pushing %.2f. Head is now %.2f\n",value,currentHead);
// 		}
		
	
// 	}

//     return 0;
// }