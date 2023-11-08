
#ifndef _heap_H
#define _heap_H 1
#include "data_structures.h"

extern int heapifyCalls;

void swap(ELEMENT **a, ELEMENT **b);
void Heapify(HEAP *h, int i);
void BuildHeap(HEAP *h, ELEMENT **A, int n);
ELEMENT *ExtractMin(HEAP *h);
void DecreaseKey(HEAP *h, int i, double newKey);
void Insertion(HEAP *h, ELEMENT *x);
bool IsMinHeap(HEAP *heap);
void freeHeap(HEAP* h);



#endif
