/**
 * 
 * Priority queue
 * 
 * Implementation using heap
 * 
 * 
 * 
 *  Heap is an array.
 *      Array consists of nodes.
 *          In node are stored:
 *          - value:    priority value
 *          - data:     data structure of anything
 * 
 * */

typedef struct Data {
    /**
     * Anything can be added here
     * */
} heap_data;


typedef struct Node {
    int value;
    heap_data data;
} heap_node;


typedef struct Heap {
    heap_node *heap_array;
    int size;
} Heap;



/**
 * 
 * 
 * 
 * */

void swap(heap_node *a, heap_node *b);
void insert(heap_node new_node, heap_node *array, int size);
void shiftDown(heap_node *array, int size, int index);
heap_node removeMin(heap_node *array, int size);



/**
 * 
 * Priority queue methods
 * 
 * */

void init_heap(Heap *heap, int size);
void enqueue(Heap *heap, heap_node new_node);
heap_node dequeue(Heap *heap);
