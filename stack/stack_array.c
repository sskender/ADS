#include <stdio.h>
#define MAX 100


typedef struct stack {
    int array[MAX];
    int top;
} Stack;


void init_stack(Stack *stack) {
    stack->top = -1;
}


int isEmpty(Stack *stack) {
    return stack->top < 0;
}


int isFull(Stack *stack) {
    return stack->top >= MAX-1;
}


int push(int data, Stack *stack) {

    if (isFull(stack)) {
        return 0;
    }

    stack->array[++stack->top] = data;

    return 1;
}


int pop(int *data, Stack *stack) {

    if (isEmpty(stack)) {
        return 0;
    }

    *data = stack->array[stack->top--];

    return 1;
}


int main(void) {
    int data, result;
    Stack stack;

    init_stack(&stack);

    push(1, &stack);
    result = pop(&data, &stack);
    printf("Result: %d Data: %d\n", result, data);

    push(2, &stack);
    pop(&data, &stack);

    result = pop(&data, &stack);
    printf("Result: %d Data: %d\n", result, data);

    return 0;
}
