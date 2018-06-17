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


int queuePeek(int *data, Queue *queue) {
    Queue temp_queue;
    int temp_data;

    /* it is empty */
    if (!dequeue(&temp_data, queue)) {
        return 0;
    }

    /* not empty */
    *data = temp_data;

    init_queue(&temp_queue);
    enqueue(temp_data, &temp_queue);

    while (dequeue(&temp_data, queue)) {
        enqueue(temp_data, &temp_queue);
    }

    while(dequeue(&temp_data, &temp_queue)) {
        enqueue(temp_data, queue);
    }

    return 1;
}


int queuePeekIndex(int *data, Queue *queue, int index) {
    Queue temp_queue;
    int temp_data;
    int i = 0, found = 0;

    init_queue(&temp_queue);

    while (dequeue(&temp_data, queue)) {
        
        if (i == index) {
            found = 1;
            *data = temp_data;
        }

        enqueue(temp_data, &temp_queue);
        i++;
    }

    while (dequeue(&temp_data, &temp_queue)) {
        enqueue(temp_data, queue);
    }

    return found;
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
    enqueue(4, &queue);

    queuePeek(&data, &queue);
    printf("Queue peek: %d\n", data);
    queuePeekIndex(&data, &queue, 1);
    printf("Queue peek at index 1: %d\n", data);

    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);
    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);
    dequeue(&data, &queue);
    printf("Empty: %d Data: %d\n", isEmpty(&queue), data);

    return 0;
}
