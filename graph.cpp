#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <cfloat>

int dijkstraRunFlag = 0;

void insertIntoAdjacencyList(NODE **ADJ, int u, int v, double w, int edgeIndex, int flag) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed for new node\n");
        return;
    }

    new_node->index = edgeIndex;
    new_node->u = u;
    new_node->v = v;
    new_node->w = w;

 //printf("Inserting edge: %d-%d with weight %f\n", u, v, w); // Debugging print

    if (flag == 1) {  // insert at the front
        new_node->next = ADJ[u - 1];
        ADJ[u - 1] = new_node;
    } else {  // insert at the rear
        if (ADJ[u - 1] == NULL) {
            ADJ[u - 1] = new_node;
        } else {
            NODE *temp = ADJ[u - 1];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
    }
}

void PrintADJ(NODE **ADJ, int n) {
    for (int i = 1; i <= n; ++i) {
        fprintf(stdout, "ADJ[%d]:", i); // Use i + 1 for 1-based indexing in output
        NODE *current = ADJ[i - 1];
        while (current) {
            fprintf(stdout,"-->[%d %d: %.2f]", current->u, current->v, current->w);
            current = current->next;
        }
        fprintf(stdout, "\n");
    }
}

void printPath(VERTEX **V, int n, int source, int destination) {
    if (!dijkstraRunFlag) {
        
        return;
    }
dijkstraRunFlag = 0;

   
    STACK *pathStack = new_stack();
    int current = destination;

    while (current != source) {
        if (current == -1 || V[current] == NULL) {
            fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
            free_stack(pathStack);
            return;
        }

        stack_push(pathStack, V[current]);
        current = V[current]->pi;
    }
    stack_push(pathStack, V[source]); // Include the source in the path

    fprintf(stdout, "The shortest path from %d to %d is:\n", source, destination);
    while (!stack_empty(pathStack)) {
        VERTEX *vertex = stack_top(pathStack);
        fprintf(stdout, "[%d:%8.2lf]", vertex->index, vertex->d);
        stack_pop(pathStack);
        if (!stack_empty(pathStack)) {
            fprintf(stdout, "-->");
        }
    }
    printf(".\n");
    dijkstraRunFlag = 1;
    free_stack(pathStack);
}

HEAP *InitializeHeap(int capacity) {
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (!heap) {
        fprintf(stderr, "Error: Memory allocation failed for heap\n");
        return NULL;
    }

    heap->H = (VERTEX **)malloc((capacity +1) * sizeof(VERTEX *));
    if (!heap->H) {
        fprintf(stderr, "Error: Memory allocation failed for heap array\n");
        free(heap);
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;
    for (int i = 1; i <= capacity; i++) {
        heap->H[i] = NULL;
    }

    return heap;
}


void dijkstra(VERTEX **V, NODE **ADJ, int n, int source, int target) {

    for (int i = 1; i <= n; i++) {
            V[i]->d = DBL_MAX;
            V[i]->pi = -1;
            V[i]->index = i;
        }
        V[source]->d = 0;
        HEAP *heap = InitializeHeap(n);
        for (int i = 1; i <= n; i++) {
            Insertion(heap, V[i]);
        }

        while (heap->size > 0) {
        ELEMENT *u = ExtractMin(heap);
        if (!u || u->d == DBL_MAX) continue;

        //printf("Processing vertex: %d with distance: %.2f\n", u->index, u->d); // Debug print
        NODE *temp = ADJ[u->index - 1];
        while (temp != NULL) {
            int v = temp->v;
            //printf("Considering edge: %d -> %d with weight %.2f\n", u->index, v, temp->w); // Debug print

            /*if (v < 1 || v > n || V[v - 1] == NULL) {
                fprintf(stderr, "Error: Invalid vertex or NULL reference\n");
                break;
            }*/

            if (V[v  ]->d > V[u->index ]->d + temp->w) {
                V[v ]->d = V[u->index ]->d + temp->w;
                V[v ]->pi = u->index;
                DecreaseKey(heap, V[v ]->position, V[v ]->d);
            }
            temp = temp->next;
        }
    }
        free(heap);
        dijkstraRunFlag = 1;
    }


void SingleSource(VERTEX **V, NODE **ADJ, int n, int source, int network03Flag, int SingleSourceCountFlag) {
    
    // Initialize single source
    for (int i = 1; i <= n; i++) {
        V[i]->d = DBL_MAX;
        V[i]->pi = -1;
        V[i]->index = i;
    }
    V[source]->d = 0;

    // Initialize the heap
    HEAP *heap = InitializeHeap(n);
    for (int i = 1; i <= n; i++) {
        Insertion(heap, V[i]);
    }

    // Relax edges repeatedly
    while (heap->size > 0) {
        ELEMENT *u = ExtractMin(heap);
        if (!u || u->d == DBL_MAX) continue;

        NODE *temp = ADJ[u->index - 1];
        while (temp != NULL) {
            int v = temp->v;
            
            if (network03Flag && SingleSourceCountFlag && V[v]->d > V[u->index]->d + temp->w) {
                V[v]->d = V[u->index]->d + temp->w;
                V[v]->pi = u->index;
            }
            
            if (network03Flag && V[v]->d > V[u->index]->d + temp->w)  {
//printf("Updating path %d -> %d, new distance: %.2f\n", u->index, v, V[u->index]->d + temp->w);                
                V[v]->d = V[u->index]->d + temp->w;
                V[v]->pi = u->index;
//printf("Pi %d become %d\n", V[v]->pi, u->index );
                DecreaseKey(heap, V[v]->position, V[v]->d);
            }
            if (!network03Flag && V[v]->d > V[u->index]->d + temp->w) {
                V[v]->d = V[u->index]->d + temp->w;
                V[v]->pi = u->index;
            }
            temp = temp->next;
        }
    }

    freeHeap(heap);
    dijkstraRunFlag = 1;
}


void PrintLength(VERTEX **V, int n, int source, int destination) {
    if (!dijkstraRunFlag) {
        fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
        return;
    }
    dijkstraRunFlag = 0;
    if (source < 1 || source > n || destination < 1 || destination > n) {
        fprintf(stderr, "Invalid vertices\n");
        return;
    }

    // Check if the destination is reachable from the source
    if (V[destination]->d == DBL_MAX) {
        fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
    } else {
        fprintf(stdout, "The length of the shortest path from %d to %d is:     %.2f\n", source, destination, V[destination]->d);
    }
}
