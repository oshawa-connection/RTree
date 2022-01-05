#pragma once
#include "../headers/Node.h"
// typedef struct PriorityQueue * PriorityQueuePtr;
typedef struct PQNode * PriorityQueuePtr;

// PriorityQueuePtr createPriorityQueue(double d, double p);

// Return the value at head
NodePtr pqPeek(PriorityQueuePtr* head);

double pqPeekPriority(PriorityQueuePtr* head);

// Removes the element with the
// highest priority form the list
void pqPop(PriorityQueuePtr* head);
 
// Function to push according to priority
void pqPush(PriorityQueuePtr* head, NodePtr dataValue, double priority);
 
// Function to check is list is empty
bool pqIsEmpty(PriorityQueuePtr* head);

/**
 * Clear all nodes out.
 * */
void pqClear(PriorityQueuePtr* head);

uint64_t pqGetLength(PriorityQueuePtr* head);

void doNothing();