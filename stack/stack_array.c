#include <stdio.h>
#include <stdlib.h>
#define EXPAND 100


typedef struct stack {
    int *array;
    int top;
    int size;
} Stack;


void init_stack(Stack *stack, int size) {
    stack->top   = -1;
    stack->array = (int *)malloc(sizeof(int)*size);
    stack->size  = (stack->array == NULL) ? 0 : size;
}


int isEmpty(Stack *stack) {
    return stack->top < 0;
}


int isFull(Stack *stack) {
    return stack->top >= stack->size-1;
}


int push(int data, Stack *stack) {
    int *array_temp;

    if (isFull(stack)) {

        array_temp = (int *)realloc(stack->array, stack->size+EXPAND);

        if (array_temp == NULL) {
            return 0;
        }
        else {
            stack->array = array_temp;
            stack->size += EXPAND;
        }
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


int peek(int *data, Stack *stack) {
    
    if (!pop(data, stack)) {
        return 0;
    }
    else {
        push(*data, stack);
        return 1;
    }
}


int peekIndex(int *data, Stack *stack, int index) {
    Stack temp_stack;
    int temp_data;
    int i = 0, found = 0;

    init_stack(&temp_stack, stack->size);

    while (pop(&temp_data, stack)) {

        if (i == index) {
            found = 1;
            *data = temp_data;
            break;
        }
        
        push(temp_data, &temp_stack);
        i++;
    }

    while (pop(&temp_data, &temp_stack)) {
        push(temp_data, stack);
    }

    return found;
}


int main(void) {
    int data, result;
    Stack stack;

    init_stack(&stack, 2);

    push(1, &stack);
    push(2, &stack);
    push(3, &stack);
    push(4, &stack);
    result = pop(&data, &stack);
    printf("Result: %d Data: %d\n", result, data);

    peek(&data, &stack);
    printf("Peek: %d\n", data);
    peekIndex(&data, &stack, 1);
    printf("Peek at index 1: %d\n", data);

    push(2, &stack);
    pop(&data, &stack);

    result = pop(&data, &stack);
    printf("Result: %d Data: %d\n", result, data);

    return 0;
}
