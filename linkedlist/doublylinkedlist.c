#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;
    struct node *prev;
};


typedef struct node Node;


Node *createNewNode(int data) {
    Node *temp;

    if ((temp = (Node *)malloc(sizeof(Node))) == NULL) {
        return NULL;
    }

    (*temp).data = data;
    (*temp).next = NULL;
    (*temp).prev = NULL;

    /**
     * NOTE: This is the same as:
     * 
     * temp->data = data;
     * temp->next = NULL;
     * temp->prev = NULL;
     * */

    return temp;
}


int addAtHead(int data, Node **headp) {
    Node *new_node = createNewNode(data);

    if (new_node == NULL) {
        return 0;
    }

    if (*headp == NULL) {
        *headp = new_node;
    }
    else {
        (*headp)->prev = new_node;
        new_node->next = *headp;
        *headp = new_node;
    }

    return 1;
}


int addAtTail(int data, Node **headp) {
    Node *temp = *headp;
    Node *new_node = createNewNode(data);

    if (new_node == NULL) {
        return 0;
    }

    if (*headp == NULL) {
        *headp = new_node;
        
        return 1;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;

    return 1;
}


void display(Node *head) {
    Node *temp = head;

    if (temp == NULL) {
        printf("List is empty\n");
    }
    else {
        printf("List elements: ");

        while (temp != NULL) {
            printf("%d", temp->data);
            temp = temp->next;

            if (temp != NULL) printf(" -> ");
        }

        printf("\n");
    }

}


void displayReverse(Node *head) {
    Node *temp = head;

    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }

    printf("Rvrs elements: ");

    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->prev;

        if (temp != NULL) printf(" -> ");
    }

    printf("\n");

}


int main(void) {
    Node *head = NULL;

    addAtHead(1, &head);
    display(head);
    displayReverse(head);

    addAtHead(2, &head);
    display(head);
    displayReverse(head);
    
    addAtTail(5, &head);
    display(head);
    displayReverse(head);

    addAtTail(6, &head);
    display(head);
    displayReverse(head);

    addAtHead(3, &head);
    display(head);
    displayReverse(head);

    return 0;
}
