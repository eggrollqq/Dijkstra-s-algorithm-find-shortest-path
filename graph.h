#ifndef _graph_H
#define _graph_H 1
#include "data_structures.h"


void insertIntoAdjacencyList(pNODE* ADJ, int u, int v, double w, int edgeIndex, int flag);
void PrintADJ(pNODE* ADJ, int n);
void printPath(pVERTEX *V, int source, int destination);
HEAP *InitializeHeap(int capacity);
void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source, int target);

#endif
