#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <cfloat>


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
    if (V[destination - 1]->d == INFINITY) {
        fprintf(stdout, "There is no path from %d to %d.\n", source, destination);
        return;
    }

    STACK *pathStack = new_stack();
    int current = destination;
    while (current != source) {
        stack_push(pathStack, V[current - 1]);
        current = V[current - 1]->pi;
    }
    stack_push(pathStack, V[source - 1]);

    fprintf(stdout, "The shortest path from %d to %d is:\n", source, destination);
    while (!stack_empty(pathStack)) {
        VERTEX *vertex = stack_top(pathStack);
        fprintf(stdout, "[%d: %.2f]", vertex->index, vertex->d);
        stack_pop(pathStack);
        if (!stack_empty(pathStack)) {
            fprintf(stdout, "-->");
        }
    }
    printf("\n");
    free_stack(pathStack);
}

HEAP *InitializeHeap(int capacity) {
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (!heap) {
        fprintf(stderr, "Error: Memory allocation failed for heap\n");
        return NULL;
    }

    heap->H = (VERTEX **)malloc((capacity + 1) * sizeof(VERTEX *));
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


void dijkstra(VERTEX **V, NODE **ADJ, int n, int source, int target, STACK *pathStack) {
    // Initialize all vertices
    for (int i = 1; i <= n; i++) {
        V[i]->d = 0;
        V[i]->pi = 0;
        V[i]->index = i;
    }
    V[source]->d = 0;

    HEAP *heap = InitializeHeap(n);
    for (int i = 1; i <= n; i++) {
        Insertion(heap, V[i]);
    }

    while (heap->size > 0) {
        ELEMENT *u = ExtractMin(heap);

if (u->index < 1 || u->index > n) {
            fprintf(stderr, "Error: Invalid index %d extracted from heap\n", u->index);
            continue;
        }

        stack_push(pathStack, V[u->index]); // Push vertex onto the stack

        if (u->index == target) {
            break;
        }

        
double count = 0;
for (int i = 1; i <= n; ++i) {
        NODE *temp = ADJ[u->index -1];
        u->index++;
        while (temp != NULL) {
            int v = temp->v;      
printf("for edge %d->%d: weight: %.2lf\n", temp->u, temp->v, temp->w);
printf("V[v]->d:%lf >V[u->index]->d: %.2lf + %.2lf\n" , ADJ[v]->w,ADJ[u->index-1]->w, temp->w);               
printf("%.2lf\n", count = count + temp->w);      
printf("%d", u->index);
printf("      %.2lf\n", ADJ[u->index-1]->w);
            if (ADJ[v]->w > ADJ[u->index]->w + temp->w) {
                ADJ[v]->w = ADJ[u->index]->w + temp->w; // Update the distance
                ADJ[v]->pi = u->index; // Update the predecessor
                DecreaseKey(heap, V[v]->position, V[v]->d); // Update the position in the heap
            }
            temp = temp->next;
        }
    }

    freeHeap(heap);
}
}
