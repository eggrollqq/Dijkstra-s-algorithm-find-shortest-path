#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <float.h>

void insertIntoAdjacencyList(pNODE* ADJ, int u, int v, double w, int edgeIndex, int flag) {
    pNODE new_node = (pNODE) malloc(sizeof(NODE));
    new_node->index = edgeIndex;
    new_node->u = u;
    new_node->v = v;
    new_node->w = w;
    new_node->next = NULL;

    if (flag == 1) {  // insert at the front
        new_node->next = ADJ[u - 1];
        ADJ[u - 1] = new_node;
    } else {  // insert at the rear
        if (ADJ[u - 1] == NULL) {
            ADJ[u - 1] = new_node;
        } else {
            pNODE temp = ADJ[u - 1];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }
}

void PrintADJ(NODE* ADJ[], int n) {
    for (int i = 1; i <= n; i++) {
        fprintf(stdout, "ADJ[%d]:", i);
        NODE* current = ADJ[i - 1]; // Change this line
        while (current != NULL) {
            fprintf(stdout, "-->[%d %d: %.2f]", current->u, current->v, current->w);
            current = current->next;
        }
        fprintf(stdout, "\n");
    }
}

void printPath(pVERTEX *V, int source, int destination) {
    
    if (V[destination]->d == DBL_MAX) {
        printf("There is no path from %d to %d.\n", source, destination);
        return;
    }
       // Use a stack or other structure to store and then print the path in reverse
    // This part of the implementation depends on how you want to handle the path retrieval
    int stackSize = 0;
    int current = destination;
    while (current != 0) {
        stackSize++;
        current = V[current]->pi;
    }

    int *pathStack = (int *)malloc(stackSize * sizeof(int));
    double *distStack = (double *)malloc(stackSize * sizeof(double));
    current = destination;
    int i = 0;
    while (current != 0) {
        pathStack[i] = current;
        distStack[i] = V[current]->d;
        current = V[current]->pi;
        i++;
    }

    printf("The shortest path from %d to %d is:\n", source, destination);
    for (int j = stackSize - 1; j >= 0; j--) {
        printf("[%d: %5.2f]", pathStack[j], distStack[j]);
        if (j > 0) {
            printf("-->");
        }
    }
    printf(".\n");

    free(pathStack);
    free(distStack);

 
}


