#ifndef data_structure_H
#define data_structure_H

typedef enum {
    white,
    black,
    grey,  
} COLOR;

typedef struct TAG_VERTEX{
int index;
COLOR color;
double d;
int pi;
int position;
}VERTEX;

typedef VERTEX *pVERTEX;


typedef struct TAG_NODE{
int index;
int u;
int v;
double w;
TAG_NODE *next;
}NODE;

typedef NODE *pNODE;

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;




typedef struct TAG_HEAP{
int capacity;
int size;
pELEMENT *H;
}HEAP;

typedef HEAP *pHEAP;


typedef struct TAG_LISTSTACK {
    pVERTEX vertex;              // pointer to the vertex information
    struct TAG_LISTSTACK* next;  // pointer to the next node in the stack
} LISTSTACK;

typedef LISTSTACK* pLISTSTACK;

typedef struct TAG_STACK {
    pLISTSTACK top;            // pointer to the top node in the stack
    int size;                  // current size of the stack
} STACK;

typedef STACK* pSTACK;

#endif