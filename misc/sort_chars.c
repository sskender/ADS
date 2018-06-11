#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 10


void swap(char *a, char *b){
    char *temp;
    temp = (char *)malloc(LENGTH*sizeof(char)+1);
    
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
    
    free(temp);	
}


void insertionSort(char **A, int n, int direction) {
    int i, hole;
    char *temp;

    /* ascending */
    if (direction == 0) {

        for(i = 1; i < n; i++) {
            hole = i;
            temp = A[hole];

            while (hole > 0 && strcmp(A[hole-1], temp) > 0) {
                A[hole] = A[hole-1];
                hole--;
            }

            A[hole] = temp;
        }

    }
    /* descending */
    else {

        for(i = 1; i < n; i++) {
            hole = i;
            temp = A[hole];

            while (hole > 0 && strcmp(A[hole-1], temp)  < 0) {
                A[hole] = A[hole-1];
                hole--;
            }

            A[hole] = temp;
        }

    }
}


void selectionSort(char **A, int n, int direction) {
    int i, j;
    int min;

    /* ascending */
    if (direction == 0) {

        for(i = 0; i < n - 1; i++) {
            min = i;

            for(j = i + 1; j < n; j++) {
                if (strcmp(A[j], A[min]) > 0) {
                    min = j;
                }
            }

            swap(A[i], A[min]);
        }

    }
    /* descending */
    else {

        for(i = 0; i < n - 1; i++) {
            min = i;

            for(j = i + 1; j < n; j++) {
                if (strcmp(A[j], A[min]) < 0) {
                    min = j;
                }
            }

            swap(A[i], A[min]);
        }

    }

}


void bubbleSortImproved(char **A, int n, int direction) {
    int i, j;
    int swapped;

    /* ascending */
    if (direction == 0) {

        for(i = 0, swapped = 1; swapped == 1; i++) {
            swapped = 0;

            for(j = 0; j < n - i - 1; j++) {
                if (strcmp(A[j], A[j+1]) > 0) {
                    swap(A[j], A[j+1]);
                    swapped = 1;
                }
            }
        }

    }
    /* descending */
    else {

        for(i = 0, swapped = 1; swapped == 1; i++) {
            swapped = 0;

            for(j = 0; j < n - i - 1; j++) {
                if (strcmp(A[j], A[j+1]) < 0) {
                    swap(A[j], A[j+1]);
                    swapped = 1;
                }
            }
        }

    }

}


void shellSort(char **A, int n, int direction) {
    int i, j, gap;
    char *temp;

    /* ascending */
    if (direction == 0) {

        for(gap = n / 2; gap > 0; gap /= 2) {
            
            for(i = gap; i < n; i++) {
                temp = A[i];
                j = i;
            
                while (j >= gap && strcmp(A[j-gap], temp) > 0) {
                    A[j] = A[j-gap];
                    j -= gap;
                }

                A[j] = temp;
            }

        }

    }
    /* descending */
    else {

        for(gap = n / 2; gap > 0; gap /= 2) {

            for(i = gap; i < n; i++) {
                temp = A[i];
                j = i;

                while (j >= gap && strcmp(A[j-gap], temp) < 0) {
                    A[j] = A[j-gap];
                    j -= gap;
                }

                A[j] = temp;
            }
        }

    }

}


void shellSort_Hibbard(char **A, int n, int direction) {
    int i, j, gap;
    char *temp;
    int exp = 2;

    while (exp <= n) {
        exp *= 2;
    }
    exp /= 2;

    /* ascending */
    if (direction == 0) {

        for(gap = exp - 1; gap > 0; gap = exp - 1, exp /= 2) {

            for(i = gap; i < n; i++) {
                temp = A[i];
                j = i;

                while (j >= gap && strcmp(A[j-gap], temp) > 0) {
                    A[j] = A[j-gap];
                    j -= gap;
                }

                A[j] = temp;
            }
        }

    }
    /* descending */
    else {

        for(gap = exp - 1; gap > 0; gap = exp - 1, exp /= 2) {

            for(i = gap; i < n; i++) {
                temp = A[i];
                j = i;

                while (j >= gap && strcmp(A[j-gap], temp) < 0) {
                    A[j] = A[j-gap];
                    j -= gap;
                }

                A[j] = temp;
            }
        }

    }

}


int main(void) {
    int n, i;
    char **A;

    scanf("%d", &n);
    A = malloc(n*sizeof(*A));

    getchar();  /* grab new line */
    for(i = 0; i < n; i++) {
        A[i] = malloc(LENGTH*sizeof(char)+1);
        gets(A[i]);
    }

    insertionSort(A, n, 1);
    selectionSort(A, n, 1);
    bubbleSortImproved(A, n, 1);
    shellSort(A, n, 1);
    shellSort_Hibbard(A, n, 1);

    printf("\nSorted:\n");
    for(i = 0; i < n; i++) {
        printf("%s\n", A[i]);
    }

    free(A);

    return 0;
}