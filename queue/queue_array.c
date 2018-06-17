#include <stdio.h>
#include <stdlib.h>
#define EXPAND 100


struct queue {
    int *array;
    int in;
    int out;
    int size;
};

typedef struct queue Queue;


void init_queue(Queue *queue, int size) {
    queue->array = (int *)malloc(sizeof(int)*size);
    queue->size  = (queue->array == NULL) ? 0 : size;
    queue->in    = 0;
    queue->out   = 0;
}


int isEmpty(Queue *queue) {
    return queue->in == queue->out;
}


int isFull(Queue *queue) {
    return (queue->in+1) % queue->size == queue->out;
}


int enqueue(int data, Queue *queue) {
    int *array_temp;

    if (isFull(queue)) {
        
        array_temp = (int *)realloc(queue->array, queue->size+EXPAND);
        
        if (array_temp == NULL) {
            return 0;
        }
        else {
            queue->array = array_temp;
            queue->size += EXPAND;
        }
    }

    queue->in++;
    queue->in %= queue->size;
    queue->array[queue->in] = data;

    return 1;
}


int dequeue(int *data, Queue *queue) {
    if (isEmpty(queue)) {
        return 0;
    }

    queue->out++;
    queue->out %= queue->size;
    
    *data = queue->array[queue->out];

    return 1;
}


int queuePeek(int *data, Queue *queue) {
    Queue temp_queue;
    int temp_data;

    /* empty */
    if (!dequeue(&temp_data, queue)) {
        return 0;
    }

    /* not empty */
    *data = temp_data;

    init_queue(&temp_queue, queue->size);
    enqueue(temp_data, &temp_queue);

    while (dequeue(&temp_data, queue)) {
        enqueue(temp_data, &temp_queue);
    }

    while (dequeue(&temp_data, &temp_queue)) {
        enqueue(temp_data, queue);
    }

    return 1;
}


int queuePeekIndex(int *data, Queue *queue, int index) {
    Queue temp_queue;
    int temp_data;
    int i = 0, found = 0;

    init_queue(&temp_queue, queue->size);

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

    init_queue(&queue, 2);

    enqueue(1, &queue);
    enqueue(2, &queue);
    enqueue(3, &queue);
    enqueue(4, &queue);

    queuePeek(&data, &queue);
    printf("Queue peek: %d\n", data);
    queuePeekIndex(&data, &queue, 2);
    printf("Queue peek at index 2: %d\n", data);

    dequeue(&data, &queue);
    dequeue(&data, &queue);
    dequeue(&data, &queue);

    printf("Data: %d\n", data);
    printf("Empty: %d\n", isEmpty(&queue));

    return 0;
}
