#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 256    /* prefixed table size */
#define W 8         /* (256 = 2^8  ==>  w = 8) */

#define RANDTOP 99999
#define RANDBOT 10000


struct node {
    int ID;
    char *name;
    char age;
    struct node *link;
};


struct HashTable {
    /* table of nodes (with hashed data) */
    struct node *table[SIZE];
    int size;
};


/* aliases */
typedef struct node node;
typedef struct HashTable Hash;


/* hash table initialization */
void init_hash(int size, Hash *hash);


/* addressing methods */
unsigned long int getAddressByMultiplication(int key);
unsigned long int getAddressByDivision(int size, int key);


/**
 * print output
 * 
 * Sheme:
 *      If numbers are: 4, 10, 2, 350, 25, 12, 478
 * 
 *      1) Linear:
 *          0.      4
 *          1.     10
 *          2.      2
 *          3.     25 *
 *          4.     12 *
 *          5.    478 *
 *          6.
 *          n.     350
 * 
 *      2) Quadratic probing:
 *          0.      4
 *          1.     10
 *          2.      2
 *          3.     12 *
 *          4.     25 *
 *          5.      
 *          6.    478 *
 *          n.    350
 * 
 *      3) Linked list:
 *          0.      4       -
 *          1.     10      25 *    -
 *          2.      2      12 *   478 *    -
 *          3.      -
 *          4.      -
 *          5.      -
 *          6.      -
 *          n.    350       -
 * 
 *      collisions are marked with *
 * */
void displayHashTable(Hash *hash);


/* NOTE: open addressing */
/* NOTE: linear probing method */
/**
 * Sheme:
 *                           __
 * hash(Node1) -----------> |_|             Node1 to index 0.
 * hash(Node2) -------|     |_|
 * hash(Node3) -------|---> |_|             Node2 to index 2.
 * hash(Node4) ----|        |_| <--         Index 2 is taken by Node2, put Node3 in next bucket (index 3).
 *                 |        |_|
 *                 |------> |_|             Node 4 to index 5.
 *                          |_|
 * 
 * */
int insertLinear(int ID, char *name, char age, Hash *hash);
int deleteLinear(int ID, Hash *hash);
node *findLinear(int ID, Hash *hash);


/* NOTE: open addressing */
/* NOTE: quadratic probing method */
/**
 * Sheme:
 *                           __
 * hash(Node1) -----------> |_|             Node1 to index 0.
 * hash(Node2) -----------> |_|             Node2 to index 1.
 * hash(Node3) -------|     |_| <--         Index 1 is taken by Node2, put Node3 in next quadratic bucket (+ 1^2 => index 2).
 * hash(Node4) -------|     |_|             Index 1 is taken by Node2, put Node4 in next quadratic bucket (+ 1^2 => index 2, + 2^2 => index 4), because index 2 is taken.
 *                          |_| <--
 *                          |_|
 *                          |_|
 *
 * */
int insertQuadratic(int ID, char *name, char age, Hash *hash);
int deleteQuadratic(int ID, Hash *hash);
node *findQuadratic(int ID, Hash *hash);


/* NOTE: open addressing */
/* NOTE: linked list probing method */
/**
 * Sheme:
 *                           __
 * hash(Node1) -----------> |_|      __     Node1 to index 0.
 * hash(Node2) -----------> |_| --> |_|     Node2 to index 1, Node3 append to bucket with index 1. (linked list pointer connection)
 * hash(Node3) -------|     |_| 
 * hash(Node4) ----|        |_|
 *                 |------> |_|             Node4 to index 4.
 *                          |_|
 *                          |_|
 * 
 * */
int insertLinkedList(int ID, char *name, char age, Hash *hash);
int deleteLinkedList(int ID, Hash *hash);
node *findLinkedList(int ID, Hash *hash);



int main(void) {
    int i, randint;
    int rand_l[SIZE+100], rand_q[SIZE+100], rand_ll[SIZE+100];
    int fail_l = 0, fail_q = 0, fail_ll = 0;
    Hash hash_l, hash_q, hash_ll;
    node *search;

    srand((unsigned)time(NULL));
    

    /* 1 linear */
    init_hash(SIZE, &hash_l);
    
    for(i = 0; i < 50; i++) {
        randint = rand() % (RANDTOP - RANDBOT + 1) + RANDBOT;
        rand_l[i] = randint;
        fail_l += !insertLinear(randint, "Magi", 18, &hash_l);
    }

    printf("Linear failed: %d\n", fail_l);
    displayHashTable(&hash_l);

    printf("\nFind in linear: ");
    search = findLinear(rand_l[5], &hash_l);
    if (search != NULL) {
        printf("Search ID: %d => %d: %s (%2d)\n", rand_l[5],search->ID, search->name, search->age);
        printf("Deleting ... ");
        deleteLinear(rand_l[5], &hash_l);
        search = findLinear(rand_l[5], &hash_l);
        printf("%s\n\n", (search == NULL) ? "Deleted!" : "Not deleted!");
        displayHashTable(&hash_l);
    }
    else {
        printf("Element with ID %d not found!\n\n", rand_l[5]);
    }


    /* 2 quadratic */
    init_hash(SIZE, &hash_q);

    for(i = 0; i < 50; i++) {
        randint = rand() % (RANDTOP - RANDBOT + 1) + RANDBOT;
        rand_q[i] = randint;
        fail_q += !insertQuadratic(randint, "Marina", 19, &hash_q);
    }

    printf("\n\nQuadratic failed: %d\n", fail_q);
    displayHashTable(&hash_q);

    printf("\nFind in quadratic: ");
    search = findQuadratic(rand_q[2], &hash_q);
    if (search != NULL) {
        printf("Search ID: %d => %d: %s (%2d)\n", rand_q[2],search->ID, search->name, search->age);
        printf("Deleting ... ");
        deleteQuadratic(rand_q[2], &hash_q);
        search = findQuadratic(rand_q[2], &hash_q);
        printf("%s\n\n", (search == NULL) ? "Deleted!" : "Not deleted!");
        displayHashTable(&hash_q);
    }
    else {
        printf("Element with ID %d not found!\n\n", rand_q[2]);
    }


    /* 3 linked list */
    init_hash(SIZE, &hash_ll);

    for(i = 0; i < 50; i++) {
        randint = rand() % (RANDTOP - RANDBOT + 1) + RANDBOT;
        rand_ll[i] = randint;
        fail_ll += !insertLinkedList(randint, "Roza", 20, &hash_ll);
    }

    printf("\n\nLinked list failed: %d\n", fail_ll);
    displayHashTable(&hash_ll);

    printf("\nFind in linked list: ");
    search = findLinkedList(rand_ll[70], &hash_ll);
    if (search != NULL) {
        printf("Search ID: %d => %d: %s (%2d)\n", rand_ll[70],search->ID, search->name, search->age);
        printf("Deleting ... ");
        deleteLinkedList(rand_ll[70], &hash_ll);
        search = findLinkedList(rand_ll[70], &hash_ll);
        printf("%s\n\n", (search == NULL) ? "Deleted!" : "Not deleted!");
        displayHashTable(&hash_ll);
    }
    else {
        printf("Element with ID %d not found!\n\n", rand_ll[70]);
    }   


    return 0;
}



/**
 *  ALL FUNCTION ARE HERE BELOW
 * */
void init_hash(int size, Hash *hash) {
    int i;

    for(i = 0; i < size; i++) {
        hash->table[i] = NULL;
    }

    hash->size = size;
}


unsigned long int getAddressByMultiplication(int key) {
    /* Knuth multiplicative hash for 32-bit numbers (data in nodes is of type int) */
    static const long int A = 2654435769;
    static const int shift = 32 - W;

    return (A * key) >> shift;
}


unsigned long int getAddressByDivision(int size, int key) {
    return key % size;
}


void displayHashTable(Hash *hash) {
    int i;
    node *temp;

    for(i = 0; i < hash->size; i++) {
        printf("%3d: ", i);

        temp = hash->table[i];

        while (temp != NULL) {
            printf("\t%d: %s (%2d)", temp->ID, temp->name, temp->age);
            temp = temp->link;
        }

        printf("\t    -\n");
    }
}


int insertLinear(int ID, char *name, char age, Hash *hash) {
    unsigned long int index;
    int i;
    node *temp;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    if ((temp = (node *)malloc(sizeof(node))) == NULL) {
        return 0;
    }
    if ((temp->name = (char *)malloc(sizeof(char)*(strlen(name)+1))) == NULL) {
        return 0;
    }

    strcpy(temp->name, name);
    temp->ID = ID;
    temp->age = age;
    temp->link = NULL;

    for(i = 0; i < hash->size; i++) {
        index = (adr + i) % hash->size;

        if (hash->table[index] == NULL) {
            hash->table[index] = temp;
            return 1;
        }
    }

    return 0;
}


int deleteLinear(int ID, Hash *hash) {
    unsigned long int index;
    int i;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    for(i = 0; i < hash->size; i++) {
        index = (adr + i) % hash->size;

        if (hash->table[index] != NULL) {
         
            if (hash->table[index]->ID == ID) {
                free(hash->table[index]);
                hash->table[index] = NULL;
     
                return 1;
            }
        }
    }

    return 0;
}


node *findLinear(int ID, Hash *hash) {
    unsigned long int index;
    int i;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    for(i = 0; i < hash->size; i++) {
        index = (adr + i) % hash->size;

        if (hash->table[index] != NULL) {

            if (hash->table[index]->ID == ID) {
                return hash->table[index];
            }
        }
    }

    return NULL;
}


int insertQuadratic(int ID, char *name, char age, Hash *hash) {
    unsigned long int index;
    int i;
    node *temp;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    if ((temp = (node *)malloc(sizeof(node))) == NULL) {
        return 0;
    }
    if ((temp->name = (char *)malloc(sizeof(char)*(strlen(name)+1))) == NULL) {
        return 0;
    }
    
    strcpy(temp->name, name);
    temp->ID = ID;
    temp->age = age;
    temp->link = NULL;

    for(i = 0; i < hash->size; i++) {
        index = (adr + i * i) % hash->size;

        if (hash->table[index] == NULL) {
            hash->table[index] = temp;
            return 1;
        }
    }

    return 0;
}


int deleteQuadratic(int ID, Hash *hash) {
    unsigned long int index;
    int i;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    for(i = 0; i < hash->size; i++) {
        index = (adr + i * i) % hash->size;

        if (hash->table[index] != NULL) {

            if (hash->table[index]->ID == ID) {
                free(hash->table[index]);
                hash->table[index] = NULL;

                return 1;
            }
        }
    }

    return 0;
}


node *findQuadratic(int ID, Hash *hash) {
    unsigned long int index;
    int i;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    for(i = 0; i < hash->size; i++) {
        index = (adr + i * i) % hash->size;

        if (hash->table[index] != NULL) {
            
            if (hash->table[index]->ID == ID) {
                return hash->table[index];
            }
        }
    }

    return NULL;
}


int insertLinkedList(int ID, char *name, char age, Hash *hash) {
    unsigned long int index;
    node *temp;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    if ((temp = (node *)malloc(sizeof(node))) == NULL) {
        return 0;
    }
    if ((temp->name = (char *)malloc(sizeof(char)*(strlen(name)+1))) == NULL) {
        return 0;
    }

    index = adr % hash->size;

    strcpy(temp->name, name);
    temp->ID = ID;
    temp->age = age;
    temp->link = hash->table[index];
    hash->table[index] = temp;

    return 1;
}


int deleteLinkedList(int ID, Hash *hash) {
    unsigned long int index;
    node *temp, *delete_this_one;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    index = adr % hash->size;
    temp = hash->table[index];

    if (temp != NULL && temp->ID == ID) {

        hash->table[index] = temp->link;
        free(temp);

        return 1;
    }

    while (temp != NULL && temp->link != NULL) {

        if (temp->link->ID == ID) {
            
            delete_this_one = temp->link;
            temp->link = temp->link->link;
            free(delete_this_one);
            
            return 1;
        }
        else {
            temp = temp->link;
        }

    }

    return 0;   /* success if not there? but nothing is done so 0? fuck me... */
}


node *findLinkedList(int ID, Hash *hash) {
    unsigned long int index;
    node *temp;

    unsigned long int adr = getAddressByMultiplication(ID);
    /* unsigned long int adr = getAddressByDivision(hash->size, ID); */

    index = adr % hash->size;
    temp = hash->table[index];

    while (temp != NULL) {

        if (temp->ID == ID) {
            return temp;
        }
        else {
            temp = temp->link;
        }
    }

    return NULL;
}
