#include "header.h"


void selectionSort(int A[], int n) {
    int i, j;
    int min;

    for(i = 0; i < n - 1; i++) {

        /* this is the smallest element (for now) */
        min = i;

        /* find smaller elements on the right to the end of the list */
        for(j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }

        /* put the smallest before others */
        swap(&A[i], &A[min]);
    }
}