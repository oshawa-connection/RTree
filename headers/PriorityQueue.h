#pragma once
// typedef struct PriorityQueue * PriorityQueuePtr;
typedef struct PQNode * PriorityQueuePtr;

PriorityQueuePtr createPriorityQueue(double d, double p);

// Return the value at head
double pqPeek(PriorityQueuePtr* head);
 
// Removes the element with the
// highest priority form the list
void pqPop(PriorityQueuePtr* head);
 
// Function to push according to priority
void pqPush(PriorityQueuePtr* head, double dataValue, double priority);
 
// Function to check is list is empty
bool pqIsEmpty(PriorityQueuePtr* head);