#include <stdlib.h>
#include "header.h"


void swap(heap_node *a, heap_node *b) {
    heap_node temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


void insert(heap_node new_node, heap_node *array, int size) {
    int index;

    index = size + 1;
    array[index] = new_node;
    
    while(array[index].value < array[index/2].value && index > 1){
    
        swap(&array[index], &array[index/2]);
        index /= 2;
    }
    
}


void shiftDown(heap_node *array, int size, int index) {
    int child_index;

    do {
        child_index = index * 2;

        if (child_index > size) {
            break;
        }

        if ((child_index < size) && (array[child_index].value > array[child_index+1].value)) {
            child_index++;
        }

        if (array[child_index].value < array[index].value) {
            swap(&array[child_index], &array[index]);
            index = child_index;
        }
        else {
            break;
        }

    } while (!(child_index > size));

}


heap_node removeMin(heap_node *array, int size) {
    heap_node node;

    node = array[1];
    array[1] = array[size];
    size--;
    shiftDown(array, size, 1);

    return node;
}


void init_heap(Heap *heap, int size) {

    heap->size = 0;
    heap->heap_array = (heap_node *)malloc(sizeof(heap_node)*(size+1));
}


void enqueue(Heap *heap, heap_node new_node) {

    insert(new_node, heap->heap_array, heap->size);
    heap->size++;
}


heap_node dequeue(Heap *heap) {
    heap_node node;

    node = removeMin(heap->heap_array, heap->size);
    heap->size--;

    return node;
}
