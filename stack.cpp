#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


STACK *new_stack() {
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    if (!stack) {
        fprintf(stderr, "Error: Memory allocation failed for new stack\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int stack_empty(STACK *stack) {
    if (!stack) {
        fprintf(stderr, "Error: Stack is NULL\n");
        return 1; // True, as the stack can be considered empty
    }
    return (stack->top == NULL);
}

void stack_push(STACK *stack, VERTEX *vertex) {
    LISTSTACK *newNode = (LISTSTACK *)malloc(sizeof(LISTSTACK));
    if (!newNode) {
        fprintf(stderr, "Error: Memory allocation failed for stack node\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = vertex;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

VERTEX *stack_top(STACK *stack) {
    if (stack_empty(stack)) {
        fprintf(stderr, "Error: Stack is empty\n");
        return NULL;
    }
    return stack->top->vertex;
}

VERTEX *stack_pop(STACK *stack) {
    if (stack_empty(stack)) {
        return NULL;
    }
    LISTSTACK *temp = stack->top;
    VERTEX *vertex = temp->vertex;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return vertex;
}

void free_stack(STACK *stack) {
    if (!stack) {
        return;
    }

    while (!stack_empty(stack)) {
        stack_pop(stack);
    }

    free(stack);
}
