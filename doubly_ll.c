#include <stdio.h>
#include <stdlib.h>

int nodeAmount; // size of the LL

// structures
typedef struct node node;

struct node {
    int data;
    node *next;
    node *prev;
};

node *createNode(int data);
node *createLL_insertByHead(node *head, int data); // create a LL by inserting a new node via head - LIFO
node *createLL_insertByTail(node *head, int data); // create a LL by inserting a new node via tail - FIFO
node* deleteNode(node *head, int index); // remove the nth element from head of

void printLL(node *head); // print out our LL

int main(int argc, char const *argv[])
{
    int amount, value, i;
    node *ll = NULL;
    nodeAmount = 0;

    printf("How many nodes would you like to create? : ");
    scanf("%d", &amount);

    for (i = 0; i < amount; i++) {
        printf("Enter a value: ");
        scanf("%d", &value);
        //ll = createLL_insertByHead(ll, value);
        ll = createLL_insertByTail(ll, value);
    }
    printLL(ll);

    deleteNode(ll, 10);

    printLL(ll);

    return 0;
}

node *createNode(int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

node *createLL_insertByHead(node *head, int data) {
    node *temp = createNode(data);

    if (head == NULL) return temp;

    temp->next = head;
    head->prev = temp;

    nodeAmount++;

    return temp;
}

node *createLL_insertByTail(node *head, int data) {
    node *temp = createNode(data);
    node *iter = head;

    if (head == NULL) return temp;

    while (iter->next != NULL)
        iter = iter->next;

    iter->next = temp;
    temp->prev = iter;

    nodeAmount++;

    return head;
}

node* deleteNode(node *head, int index) {
    node *del, *hold, *iter = head;

    while (iter != NULL) {
        if (iter->next->data == index) {
            del = iter->next;
            hold = iter->next->next;
            iter->next = hold;
            hold->prev = iter;
            free(del);
        }
        iter = iter->next;
    }

    return head;
}

void printLL(node *head) {
    node *temp = head;
    int i;

    printf("Doubly LL:\n");
    for (i = 0; i <= nodeAmount; i++) {
        printf("o---o%s", i != nodeAmount ? " -> " : " -> NULL\n");
    }

    while (temp != NULL) {
        printf("|%3d|    ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    for (i = 0; i <= nodeAmount; i++) {
        printf("o---o%s", i != nodeAmount ? " <- " : "\n");
    }
}