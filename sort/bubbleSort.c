#include "header.h"


void bubbleSort(int A[], int n) {
    int i, j;
    int swapped;

    for(i = 0, swapped = 1; swapped == 1; i++) {

        swapped = 0;

        for(j = 0; j < n - 1 -i; j++) {

            if (A[j] > A[j+1]) {

                swap(&A[j], &A[j+1]);
                swapped = 1;

            }

        }
    }
    
}