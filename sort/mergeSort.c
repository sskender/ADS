#include <stdlib.h>
#include "header.h"


/* merge left and right sub-array into main array A */
void merge(int *A, int *AL, int *AR, int n) {

    int iL, iR, iA;
    int lenL, lenR;

    iL = iR = iA = 0;
    lenL = n / 2;
    lenR = n - lenL;


    /* fill from both */
    while (iL < lenL && iR < lenR) {

        /* element from the left is smaller */
        if (AL[iL] < AR[iR]) {
            A[iA] = AL[iL];
            iL++;
        }

        /* element from the right is smaller */
        else {
            A[iA] = AR[iR];
            iR++;
        }

        iA++;
    }


    /* there is something left in the AL */
    while (iL < lenL) {
        A[iA] = AL[iL];
        iL++;
        iA++;
    }


    /* there is something left in the AR */
    while (iR < lenR) {
        A[iA] = AR[iR];
        iR++;
        iA++;
    }
}



void mergeSort(int A[], int n) {
    int *AL, *AR;
    int i;
    int mid;

    mid = n / 2;


    /* recursion exit (one element is always sorted) */
    if (n < 2) {
        return;
    }


    AL = (int *)malloc(mid * sizeof(int));              /* from start to middle */
    AR = (int *)malloc((n - mid) * sizeof(int));        /* from middle to end   */


    /* copy to left */
    for(i = 0; i < mid; i++) {
        AL[i] = A[i];
    }

    /* copy to right */
    for(i = mid; i < n; i++) {
        AR[i-mid] = A[i];
    }


    /* break into arrays of one element */
    mergeSort(AL, mid);
    mergeSort(AR, n-mid);
    merge(A, AL, AR, n);

}