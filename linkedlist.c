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
    /* double pointer because element can be added in front of all the others */
    /* in that case pointer to root must be changed to that new element */
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



void appendNode(node **rootp, int newdata) {
    /**
     *  WARNING    
     * This kills sorting logic, added element will not be sorted anymore
     * */

    node *temp;
    
    temp = (node *)malloc(sizeof(node));
    temp->data = newdata;
    temp->link = NULL;

    if (*rootp == NULL) {
        *rootp = temp;
    }
    else {
        node *p = *rootp;

        while (p->link != NULL) {
            p = p->link;
        }

        p->link = temp;
    }

}



void deleteNode(node **rootp, int deldata) {
    /* double pointer because the first element can be deleted */
    /* in that case pointer to root must be changed to that new element (second element) */
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



void copyList(node *root1, node **root2) {
    /* pointer to pointer so root2 can be changed from NULL */

    while (root1 != NULL) {

        *root2 = (node *)malloc(sizeof(node));

        (*root2)->data = root1->data;
        (*root2)->link = NULL;

        root2 = &((*root2)->link);
        root1 = root1->link;
    }

}



void mergeLists(node **root1, node *root2) {
    /* double pointer in case root1 is null and must be changed */
    /* merge and preserve sorting */

    /* iterate through second node */
    while (root2 != NULL) {
        addNode(root1, root2->data);
        root2 = root2->link;
    }
}



void appendList(node *root1, node **root2) {
    /**
     *  WARNING
     * This kills sorting logic
     * */

    /* destination is empty, just change pointer */
    if (*root2 == NULL) {
        *root2 = root1;
    }
    /* destination not null, find the end */
    else {

        node *p = *root2;

        while (p->link != NULL) {
            p = p->link;
        }

        p->link = root1;
    }

}



void deleteList(node **rootp) {

    node *temp;

    while (*rootp != NULL) {
        temp = *rootp;                                          /* save current root */
        *rootp = (*rootp)->link;                                /* change root to next element */
        free(temp);                                             /* free that node */
    }

    *rootp = NULL;                                              /* root is now null */
}



int main(void) {

    node *root  = NULL;
    node *root2 = NULL;
    node *root3 = NULL;

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
    appendNode(&root, 7);
    appendNode(&root, 8);
    display(root);

    printf("\nCopy list:\n");
    copyList(root, &root2);
    display(root);
    display(root2);

    printf("\nAdding again:\n");
    addNode(&root, 1);
    addNode(&root,3);
    addNode(&root, 4);
    display(root);

    printf("\nMerging nodes:\n");
    mergeLists(&root, root2);
    display(root);
    display(root2);

    printf("\nAppending node:\n");
    display(root);
    display(root2);
    display(root3);
    appendList(root, &root2);
    appendList(root, &root3);
    display(root);
    display(root2);
    display(root3);

    printf("\nDeleting list:\n");
    display(root3);
    deleteList(&root3);
    display(root3);
    
    return 0;
}
