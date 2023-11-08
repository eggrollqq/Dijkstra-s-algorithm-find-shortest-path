#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"

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
    if (V[destination]->d == INFINITY) {
        printf("There is no path from %d to %d.\n", source, destination);
        return;
    }

    // Your stack implementation seems to be incorrect. Here's a correction:
    int stackSize = 0;
    int current = destination;
    while (current != source) { // The loop should continue until it reaches the source
        stackSize++;
        current = V[current]->pi; // Make sure V[current]->pi is set correctly in dijkstra
    }
    stackSize++; // Include the source in the path size

    int *pathStack = (int *)malloc(stackSize * sizeof(int));
    double *distStack = (double *)malloc(stackSize * sizeof(double));
    current = destination;
    int i = 0;
    while (current != 0) {
        pathStack[i] = current;
        distStack[i] = V[current]->d;
        current = V[current]->pi; // This should lead back to the source
        i++;
    }

    printf("The shortest path from %d to %d is:\n", source, destination);
    for (int j = stackSize - 1; j >= 0; j--) { // Reverse the stack to print in correct order
        printf("[%d: %5.2f]", pathStack[j], distStack[j]);
        if (j > 0) {
            printf("-->");
        }
    }
    printf(".\n");

    free(pathStack);
    free(distStack);
}


void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source, int target) {
    // Initialize all vertices
    for (int i = 1; i <= n; i++) {
        V[i]->d = INFINITY;
        V[i]->pi = 0;
    }
    V[source]->d = 0;

    // Create a min-heap and insert all vertices
    HEAP *heap = InitializeHeap(n);
    for (int i = 1; i <= n; i++) {
        Insertion(heap, V[i]);
    }

    while (heap->size > 0) {
        ELEMENT *u = ExtractMin(heap);

        // Stop if the target is reached
        if (u->index == target) {
            break;
        }

        // Relax edges
        pNODE temp = ADJ[u->index];
        while (temp != NULL) {
            int v = temp->v;
            if (V[v]->d > V[u->index]->d + temp->w) {
                V[v]->d = V[u->index]->d + temp->w;
                V[v]->pi = u->index;
                DecreaseKey(heap, V[v]->position, V[v]->d);
            }
            temp = temp->next;
        }
    }
    free(heap);
}

HEAP *InitializeHeap(int capacity) {
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (heap == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for heap\n");
        free(heap);
        return NULL;
    }

    // The heap array (H) will store pointers to VERTEX, thus the type is pELEMENT*
    heap->H = (pELEMENT *)malloc((capacity + 1) * sizeof(pELEMENT));
    if (heap->H == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for heap array\n");
        free(heap);
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;

    // Initialize all elements to NULL
    for (int i = 1; i <= capacity; i++) {
        heap->H[i] = NULL;
    }

    return heap;

}
