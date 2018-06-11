#include <stdio.h>
#define MAX 100


struct queue {
    int array[MAX];
    int in;
    int out;
};


typedef struct queue Queue;


void init_queue(Queue *queue) {
    queue->in  = 0;
    queue->out = 0;
}


int isEmpty(Queue *queue) {
    return queue->in == queue->out;
}


int isFull(Queue *queue) {
    return (queue->in+1) % MAX == queue->out;
}


int enqueue(int data, Queue *queue) {
    if (isFull(queue)) {
        return 0;
    }

    queue->in++;
    queue->in %= MAX;
    queue->array[queue->in] = data;

    return 1;
}


int dequeue(int *data, Queue *queue) {
    if (isEmpty(queue)) {
        return 0;
    }

    queue->out++;
    queue->out %= MAX;
    
    *data = queue->array[queue->out];

    return 1;
}


int main(void) {
    Queue queue;
    int data;

    init_queue(&queue);

    enqueue(1, &queue);
    enqueue(2, &queue);

    dequeue(&data, &queue);
    dequeue(&data, &queue);

    printf("Data: %d\n", data);
    printf("Empty: %d\n", isEmpty(&queue));

    return 0;
}
