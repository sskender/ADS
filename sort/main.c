#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define TOP 999
#define BOT 0


int main(void) {
    int n, i;
    int *A;

    printf("Number of elements: ");
    scanf("%d", &n);

    A = (int *)malloc(n*sizeof(int));
    if (A == NULL) {
        printf("Not enought memory!\n");
        exit(1);
    }

    srand((unsigned)time(NULL));
    for(i = 0; i < n; i++) {
        *(A+i) = rand() % (TOP - BOT + 1) + BOT;
    }


    /*selectionSort(A, n);*/
    /*bubbleSort(A, n);*/
    /*insertionSort(A, n);*/
    /*shellSort(A, n);*/
    /*mergeSort(A, n);*/
    /*quickSort(A, 0, n);*/


    for(i = 0; i < n; i++)
        printf("%d  ", *(A+i));
    printf("\n");

    return 0;
}
