#include "header.h"

/**
 *                 gap
 *      4  1  7  9  3  5  2  6  8
 *      ^-----------^
 *         ^-----------^
 *            ^-----------^
 *               ^-----------^
 * 
 *           gap
 *      3  1  2  6  4  5  7  9  8
 *      ^-----^
 *         ^-----^
 *                  ^-----^
 *                     ^-----^
 * 
 *        gap
 *      2  1  3  6  4  5  7  9  8
 *      ^--^
 *         ^--^
 *            ^--^
 *               ^--^
 *                  ^--^
 *                     ^--^
 *                        ^--^
 *                           ^--^
 * 
 *      1  2  3  6
 *      1  2  3  4  6
 *      1  2  3  4  5  6  7  9  8
 *      1  2  3  4  5  6  7  8  9
 * 
 * */

void shellSort(int A[], int n) {
    int gap, i, j;
    int temp;

    /* first gap is the middle of the array */
    for(gap = n / 2; gap > 0; gap /= 2) {       /* this is log n */

        for(i = gap; i < n; i++) {

            temp = A[i];

            j = i;                                      /* start from middle to the right */
            while (j >= gap && A[j-gap] > temp) {       /* compare element on the far left with the element right from the gap ^^ */
                A[j] = A[j-gap];                        /* 1) swap them in the right position */
                j -= gap;                               /* always keep the same gap between two comparing elements */
            }

            A[j] = temp;                                /* 2) swap them in the right position */

        }

    }

}