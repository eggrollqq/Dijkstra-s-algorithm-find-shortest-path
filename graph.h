
#ifndef _graph_H
#define _graph_H 1
#include "data_structures.h"


void insertIntoAdjacencyList(NODE **ADJ, int u, int v, double w, int edgeIndex, int flag);
void PrintADJ(NODE **ADJ, int n);
void printPath(VERTEX **V, int n, int source, int destination);
void dijkstra(VERTEX **V, NODE **ADJ, int n, int source, int target, STACK *pathStack);

#endif
