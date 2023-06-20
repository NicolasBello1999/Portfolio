#include <stdio.h>
#include <stdlib.h>

// structures
typedef struct node node;

struct node {
    int data;
    node *next;
};

// prototypes / helper function declarations (main program)
node *createLL_rec(node *head, int data); // create a linked list recursively

node *createLL_insertByHead(node *head, int data); // create a LL by inserting a new node via head - LIFO
node *createLL_insertByTail(node *head, int data); // create a LL by inserting a new node via tail - FIFO

void printLL(node *head); // print out our LL

// functions that tackle interesting questions
node *insert_y_after_x(node *head, int x, int y);
node *insert_inOrder(node *head, int data);

int main(int argc, char const *argv[])
{
    int amount, value, i;
    node *ll = NULL;

    printf("How many nodes would you like to create? : ");
    scanf("%d", &amount);

    for (i = 0; i < amount; i++) {
        printf("Enter a value: ");
        scanf("%d", &value);
        //ll = createLL_insertByHead(ll, value);
        //ll = createLL_insertByTail(ll, value);
        ll = insert_inOrder(ll, value);
    }
    printLL(ll);

    ll = insert_y_after_x(ll, 5, 99);

    printLL(ll);
    
    return 0;
}

node* createLL_insertByHead(node *head, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    node *hold = head;

    if (head == NULL) return temp;

    temp->next = hold;

    return temp;
}

node *createLL_insertByTail(node *head, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    node *iter = head;

    if (head == NULL) return temp;

    while (iter->next != NULL)
        iter = iter->next;

    iter->next = temp;
    
    return head;
}

void printLL(node *head) {
    node *temp = head;

    printf("Singly LL:\n");
    while (temp != NULL) {
        printf("%d%s", temp->data, temp->next != NULL ? " -> " : " -> NULL\n");
        temp = temp->next;
    }
}

/* insert a new node with the value y after a node with x value; so if y = 100 and x = 8, 
   we insert a new node with value 100 after a node with value 8. */
node *insert_y_after_x(node *head, int x, int y) {
    node *iter = head;
    node *hold;
    
    while (iter != NULL) {
        if (iter->data == x) {
            hold = iter;
            node *temp = (node*)malloc(sizeof(node));
            temp->data = y;
            temp->next = hold->next;
            hold->next = temp;
        }
        iter = iter->next;
    }

    return head;
}

// insert data in ascending order meaning that the head will have the lowest value and the tail will have the greatest value
node *insert_inOrder(node *head, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    node *iter = head, *hold;

    if (head == NULL) return temp;

    if (head->data > data) { // if the head is greater than our current value
        temp->next = iter;
        return temp;
    }

    // we want to hold the node that less than our new node but the node ahead is greater than our new node as well, also checking for NULLs 
    while (iter->next->data < data && iter->next != NULL)
        iter = iter->next;

    hold = iter->next;
    iter->next = temp;
    temp->next = hold;

    return head;
}