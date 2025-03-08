#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

typedef struct NODE {
    int index, u, v;
    double w;
    struct NODE *next;
} NODE;

typedef struct {
    int index;
    double d;
    int pi;
    int position;
    NODE *ADJ;
} VERTEX;

typedef struct {
    int capacity, size;
    VERTEX **H;
} HEAP;

// Stack node structure
typedef struct LISTSTACK {
    VERTEX *vertex;
    struct LISTSTACK *next;
} LISTSTACK;

// Stack structure
typedef struct {
    LISTSTACK *top;
    int size;
} STACK;

typedef VERTEX ELEMENT;

#endif
