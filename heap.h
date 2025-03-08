#ifndef _heap_H
#define _heap_H 1
#include "data_structures.h"



void swap(VERTEX **a, VERTEX **b);
bool IsMinHeap(HEAP *heap);
void Heapify(HEAP *h, int i);
void BuildHeap(HEAP *h, VERTEX **A, int n);
VERTEX *ExtractMin(HEAP *h);
void DecreaseKey(HEAP *h, int i, double newKey);
void Insertion(HEAP *h, VERTEX *x);
void freeHeap(HEAP *h);



#endif
