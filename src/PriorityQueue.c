// C code to implement Priority Queue
// using Linked List
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Node
typedef struct node {
	// This will probably have to change to be a bbox/ node pointer.
    double data;
 
    // Lower values indicate higher priority
    double priority;
 
    struct node* next;
 
} Node;

// Function to Create A New Node
Node* createPriorityQueue(double d, double p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
double pqPeek(Node** head) {
    return (*head)->data;
}
 
// Removes the element with the
// highest priority form the list
void pqPop(Node** head) {
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
	temp = NULL;
}
 
// Function to push according to priority
void pqPush(Node** head, double dataValue, double priority) {
	// Special case when pushing to empty queue.
	if (*head == NULL) {
		*head = createPriorityQueue(dataValue, priority);
		return;
	}
    Node* start = (*head);
 
    // Create new Node
    Node* temp = createPriorityQueue(dataValue, priority);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > priority) {
 
        // Insert New Node before head
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
bool pqIsEmpty(Node** head) {
    return (*head) == NULL;
}


// // // Driver code
// int main()
// {
// 	Node* pq = createPriorityQueue(1, 1);
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