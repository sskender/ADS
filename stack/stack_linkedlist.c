#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    int data;
    struct node *link;
};


struct stack {
    struct node *top;
};


typedef struct node Node;
typedef struct stack Stack;


void init_stack(Stack *stack) {
    stack->top = NULL;
}


int isEmpty(Stack *stack) {
    return stack->top == NULL ? 1 : 0;
}


int push(int data, Stack *stack) {
    Node *temp;

    if ((temp = (Node *)malloc(sizeof(Node))) != NULL) {
        
        temp->data = data;
        temp->link = stack->top;
        stack->top = temp;
        
        return 1;
    }
    else {
        return 0;
    }
}


int pop(int *data, Stack *stack) {
    Node *temp;

    if (isEmpty(stack)) {
        return 0;
    }

    *data = stack->top->data;

    temp = stack->top->link;
    free(stack->top);
    stack->top = temp;

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

    init_stack(&temp_stack);

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

    /* check if parenthesis are valid */
    Stack stack;
    char *parenthesis = "()((()())())(())";
    int data, i = 0;

    init_stack(&stack);

    while(i++ < strlen(parenthesis)) {
        if (parenthesis[i] == '(') {
            push(parenthesis[i], &stack);
        }
        else if (parenthesis[i] == ')') {
            pop(&data, &stack);
        }
    }

    if (isEmpty(&stack)) {
        printf("Stack is empty! Parenthesis are valid.\n");
    }
    else {
        printf("Stack is not empty! Parenthesis are not valid.\n");

        while (pop(&data, &stack)) {
            printf("On stack: %c\n", data);
        }
    }

    return 0;
}
