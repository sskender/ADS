#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *link;
};


struct queue {
    struct node *front;
    struct node *rear;
};


typedef struct node Node;
typedef struct queue Queue;


void init_queue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}


int isEmpty(Queue *queue) {
    return queue->front == NULL;
}


int enqueue(int data, Queue *queue) {
    Node *temp;

    if ((temp = (Node *)malloc(sizeof(Node))) != NULL) {

        temp->data = data;
        temp->link = NULL;

        if (queue->front == NULL) {
            queue->front = temp;
            queue->rear = temp;
        }
        else {
            (queue->rear)->link = temp;
            queue->rear = temp;
        }

        return 1;
    }
    else {
        return 0;
    }
}


int dequeue(int *data, Queue *queue) {
    Node *temp;

    if (isEmpty(queue)) {
        return 0;
    }

    *data = queue->front->data;

    temp = queue->front;
    queue->front = queue->front->link;
    free(temp);

    if (isEmpty(queue)) {
        queue->rear = NULL;
    }
    
    return 1;
}


int main(void) {
    Queue queue;
    int data;

    init_queue(&queue);

    enqueue(1, &queue);
    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);

    enqueue(2, &queue);
    enqueue(3, &queue);
    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);
    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);

    return 0;
}
