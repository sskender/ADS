/**
 * 
 *  THIS IS SINGLE FILE
 *  MAIN FUNCTION INCLUDED
 * 
 *  JUST COMPILE THIS
 * 
 * */


#include <stdio.h>
#include <stdlib.h>



struct node {
    int data;
    struct node *link;
};

typedef struct node node;



void display(node *root) {

    node *temp = root;

    if (temp == NULL) {
        printf("List is empty\n");
    }
    else {
        printf("List elements: ");

        while (temp != NULL) {                                  /* not yet at the end */
            printf("%d", temp->data);                           /* current node's data */
            temp = temp->link;                                  /* next node */
            
            if (temp != NULL) printf(" -> ");                   /* just to look nicer */
        }

        printf("\n");
    }

}



int length(node *root) {

    node *temp = root;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->link;
    }

    return count;
}



node *findNode(node *root, int finddata) {                      /* return pointer to node */

    node *temp = root;

    while (temp != NULL) {                                      /* not yet at the end */
        if (temp->data == finddata) {                           /* node's data is equal to searched data */
            return temp;
        }
        temp = temp->link;                                      /* next node */
    }
    
    return NULL;
}



void addNode(node **rootp, int newdata) {

    node *temp;

    temp = (node *)malloc(sizeof(node));
    temp->data = newdata;
    temp->link = NULL;

    if (*rootp == NULL || (*rootp)->data >= newdata) {          /* smaller data is added in front */
        temp->link = *rootp;                                    /* add root after temp */
        *rootp = temp;                                          /* temp is now root element */
    }
    else {                                                      /* not adding at the beginning */
        node *p = *rootp;

        while (p->link != NULL && (p->link)->data < newdata) {
            p = p->link;                                        /* point p to next node, p is iterator */
        }

        /* result: new element (temp) is added in the middle */
        temp->link = p->link;                                   /* temp points to where p was pointing */
        p->link = temp;                                         /* p points to temp */
    }

}



void deleteNode(node **rootp, int deldata) {

    while (*rootp != NULL && (*rootp)->data != deldata) {
        rootp = &((*rootp)->link);                              /* only pointer to root is being moved, not the actual root itself */
    }

    /* at this stage either found or passed the end (not found) */
    if (*rootp != NULL) {
        *rootp = (*rootp)->link;
    }

}



void swapNodes(void) {
    /**
     *  WARNING
     * 
     * This kills current logic, array will not be sorted anymore!
     * */
}



int main(void) {

    node *root = NULL;

    printf("Adding:\n");
    display(root);
    addNode(&root, 1);
    addNode(&root, 2);
    addNode(&root, 5);
    display(root);
    addNode(&root, 4);
    display(root);
    printf("Total length: %d\n", length(root));

    printf("\nFinding:\n");
    display( findNode(root, 4) );
    display( findNode(root, 10) );

    printf("\nDeleting:\n");
    deleteNode(&root, 4);
    display(root);
    deleteNode(&root, 1);
    display(root);
    deleteNode(&root, 5);
    display(root);

    printf("\nAdding again:\n");
    addNode(&root, 13);
    addNode(&root, 1);
    display(root);

    return 0;
}
