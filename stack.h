#ifndef _stack_H
#define _stack_H 1
#include "data_structures.h"

STACK *new_stack();
int stack_empty(STACK *stack);
void stack_push(STACK *stack, VERTEX *vertex);
VERTEX *stack_top(STACK *stack);
VERTEX *stack_pop(STACK *stack);
void free_stack(STACK *stack);


#endif
