#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <float.h>



void swap(VERTEX **a, VERTEX **b) {
    VERTEX *temp = *a;
    *a = *b;
    *b = temp;
}

bool IsMinHeap(HEAP *heap) {
    if (!heap || !heap->H || heap->size == 0) {
        return false;
    }

    for (int i = heap->size / 2; i >= 1; --i) {
        if (heap->H[i]->d > heap->H[2 * i]->d) {
            return false;
        }
        if (2 * i + 1 <= heap->size && heap->H[i]->d > heap->H[2 * i + 1]->d) {
            return false;
        }
    }

    return true;
}


void Heapify(HEAP *h, int i) {

    int smallest = i;
    int l = 2 * i;
    int r = 2 * i + 1;

    if (l <= h->size && h->H[l]->d < h->H[i]->d) {
        smallest = l;
    }
    if (r <= h->size && h->H[r]->d < h->H[smallest]->d) {
        smallest = r;
    }

    if (smallest != i) {
        swap(&h->H[i], &h->H[smallest]);
        h->H[i]->position = i;        // Update position of swapped node
        h->H[smallest]->position = smallest; // Update position of smallest node
        Heapify(h, smallest);
    }
}


void BuildHeap(HEAP *h, VERTEX **A, int n) {
    h->size = n;
    h->H = A;

    for (int i = h->size / 2; i >= 1; --i) {
        Heapify(h, i);
    }
}

VERTEX *ExtractMin(HEAP *h) {
    if (!h) {
        fprintf(stderr, "Error: heap is NULL\n");
        return NULL;
    }
    if (h->size < 1) {
        fprintf(stderr, "Error: heap is empty\n");
        return NULL;
    }

    VERTEX *min = h->H[1];
    /*h->H[1] = h->H[h->size--];
    Heapify(h, 1);*/

    
    h->H[1] = h->H[h->size];
    h->H[1]->position = 1;  // Update the position of the new root
    h->size--;
    Heapify(h, 1);

    return min;
}

void DecreaseKey(HEAP *h, int i, double newKey) {
    if (!h || i < 1 || i > h->size) {
        fprintf(stderr, "Error: Invalid index for heap decrease key\n");
        return;
    }

    h->H[i]->d = newKey;
    while (i > 1 && h->H[i / 2]->d > h->H[i]->d) {
        swap(&h->H[i], &h->H[i / 2]);
        i = i / 2;
    }
}


void Insertion(HEAP *h, VERTEX *x) {
    if (h->size == h->capacity) {
        fprintf(stderr, "Error: heap is full\n");
        return;
    }

    h->H[++h->size] = x;
    int i = h->size;
    while (i > 1 && h->H[i / 2]->d > h->H[i]->d) {
        swap(&h->H[i], &h->H[i / 2]);
        i /= 2;
    }
}


void freeHeap(HEAP *h) {
    if (h) {
        free(h->H);
        free(h);
    }
}
