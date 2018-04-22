#include "header.h"


int partition(int A[], int start, int end) {
    int i;
    int pivot, pindex;

    pivot = A[end];                     /* take last element as pivot */
    pindex = start;

    /* push elements less than pivot to the left side of pivot */
    for(i = start; i < end; i++) {

        if (A[i] <= pivot) {
            swap(&A[i], &A[pindex++]);
        }

    }

    /* put pivot from the end to the right position (between smaller and bigger elements) */
    swap(&A[pindex], &A[end]);
    
    return pindex;
}


void quickSort(int A[], int start, int end) {

    int pindex;

    /* break recursion */
    if (!(start < end)) {
        return;
    }

    pindex = partition(A, start, end);

    quickSort(A, start, pindex-1);
    quickSort(A, pindex+1, end);
}