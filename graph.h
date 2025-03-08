#ifndef _graph_H
#define _graph_H 1
#include "data_structures.h"


void insertIntoAdjacencyList(NODE **ADJ, int u, int v, double w, int edgeIndex, int flag);
void PrintADJ(NODE **ADJ, int n);
void printPath(VERTEX **V, int n, int source, int destination);
void dijkstra(VERTEX **V, NODE **ADJ, int n, int source, int target);
void SingleSource(VERTEX **V, NODE **ADJ, int n, int source, int network03Flag, int SingleSourceCountFlag);
void PrintLength(VERTEX **V, int n, int source, int destination);
int findMinDist(VERTEX **V, bool *sptSet, int n);

#endif
