#include "header.h"


void swap(int *a, int *b) {
    /* goes in circle - easy to remember */
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}