#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define MAX 100


int main(void) {
    int i;
    Heap heap;
    heap_node temp;

    init_heap(&heap, MAX);

    srand((unsigned)time(NULL));

    /* enqueue */
    for(i = 0; i < MAX; ++i) {
        temp.value = rand() % 1000;
        printf("[+] Value: %4d\t\tSize: %4d\n", temp.value, heap.size);
        enqueue(&heap, temp);
    }

    printf("\n");

    /* dequeue */
    for(i = 0; i < MAX; ++i) {
        temp = dequeue(&heap);
        printf("[-] Value: %4d\t\tSize: %4d\n", temp.value, heap.size);
    }

    return 0;
}