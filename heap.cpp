#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <float.h>


void swap(pELEMENT *a, pELEMENT *b) {
    pELEMENT temp = *a;
    *a = *b;
    *b = temp;
}

bool IsMinHeap(HEAP *heap) {
    if (heap == NULL || heap->H == NULL || heap->size == 0) {
        return false;
    }
 
    for (int i = heap->size/2; i >= 1 ; i--) {
        if (heap->H[i]->d > heap->H[2*i]->d){
            return false;
        }
        if (2*i + 1 <= heap->size && heap->H[i]->d > heap->H[2*i + 1]->d) {
            return false;
        }
    }

    return true;
}

void Heapify(HEAP *h, int i) {
    
    int smallest;
    int l = 2 * i ;
    int r = 2 * i + 1;

    if (l <= h->size && h->H[l]->d < h->H[i]->d) {
        smallest = l;
    } else {
        smallest = i;
    }

    if (r <= h->size && h->H[r]->d < h->H[smallest]->d) {
        smallest = r;
    }

    if (smallest != i) {
        swap(&h->H[i], &h->H[smallest]);
        Heapify(h, smallest);
        
    }
}

void BuildHeap(HEAP *h, ELEMENT **A, int n) {
    
    h->size = n;
    h->H = A;

    for (int i = h->size / 2 ; i >= 1; i--) { 
        Heapify(h, i);
    }
    
}

ELEMENT *ExtractMin(HEAP *h) {

    if (h == NULL) {
        fprintf(stderr, "Error: heap is NULL");
        return NULL;
    }

    if (h->size < 1) {
        fprintf(stderr, "Error: heap is empty");
        return NULL;
    }
    else{
    ELEMENT *min = h->H[1];
    h->H[1] = h->H[h->size];
    h->size--;
    Heapify(h, 1);
                                        /*fprintf(stdout, "After extracting min, heap is:\n");
                                for(int i = 1; i <= h->size; i++) {
                                                fprintf(stdout, "%lf ", h->H[i]->key);
                                                    }
                                                    fprintf(stdout, "\n");*/

    return min;
    }
}

void DecreaseKey(HEAP *h, int i, double newKey) {
   printf("%d %f", i, newKey);
    h->H[i]->d = newKey;
    while (i > 1 && h->H[i / 2] != NULL && h->H[i / 2]->d > h->H[i]->d) {
        swap(&h->H[i], &h->H[i / 2]);
        i = i / 2;
    }
}


void Insertion(HEAP *h, ELEMENT *x) {
    if (h->size == h->capacity) {
        fprintf(stderr, "Error: heap is full\n");
        return;
    }

    h->size++;
    int i = h->size;
    h->H[i] = x;

    while (i > 1 && h->H[i / 2]->d > h->H[i]->d) {
        swap(&h->H[i], &h->H[i / 2]);
        i = i / 2;
    
}
                               /* fprintf(stdout, "After inserting %lf, heap is:\n", x->key);
                                                for(int i = 1; i <= h->size; i++) {
                                    fprintf(stdout, "%lf ", h->H[i]->key);
                                            }
                                                    fprintf(stdout, "\n");*/
}


void freeHeap(HEAP* h) {
    if(h != NULL) {
        for(int i = 1; i <= h->size; i++) {
            free(h->H[i]);
        }
        free(h->H);
        free(h);
    }
}

void dijkstra(pVERTEX *V, pNODE *ADJ, int n, int source) {
    // Initialize all vertices
    for (int i = 1; i <= n; i++) {
        V[i]->d = DBL_MAX;
        V[i]->pi = -1;
    }
    V[source]->d = 0;

    // Create a min-heap and insert all vertices
    HEAP *heap = InitializeHeap(n); // You need to implement this function
    for (int i = 1; i <= n; i++) {
        Insertion(heap, V[i]);
    }

    while (heap->size > 0) {
        ELEMENT *u = ExtractMin(heap);
        free(u);
        // Traverse adjacency list of u
        pNODE temp = ADJ[u->index];
        while (temp != NULL) {
            int v = temp->v;
            // Relax operation
            if (V[v]->d > u->d + temp->w) {
                V[v]->d = u->d + temp->w;
                V[v]->pi = u->index;
                DecreaseKey(heap, V[v]->position, V[v]->d); // Update heap
            }
            temp = temp->next;
            free(temp);
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
    for (int i = 0; i <= capacity; i++) {
        heap->H[i] = NULL;
    }

    return heap;

}