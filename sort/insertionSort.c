#include "header.h"


void insertionSort(int A[], int n) {
    int i;
    int hole, temp;

    for(i = 1; i < n; i++) {

        /* grab the first unsorted element
           array with one element (only the first) is already sorted */
        hole = i;           /* the second element in the first pass (index 1) */
        temp = A[hole];     /* backup that position if it gets overwritten */

        /* move  */
        while (hole > 0 && A[hole-1] > temp) {      /* element to the left bigger? */
            A[hole] = A[hole-1];                    /* then move it backwards */
            hole--;
        }

        A[hole] = temp;     /* this is useless if while does nothing ... meeh */
    }

}