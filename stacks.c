#include <stdio.h>
#include <stdlib.h>

// structures
typedef struct node node;

struct node {
    int data;
    node *next;
};

// prototypes / stack operations
void push(node **head, int data);
int pop(node **head);
int peek(node **head);
void printStack(node **head);

int main(int argc, char const *argv[])
{
    node *stack = NULL;

    push(&stack, 10);
    push(&stack, 15);
    push(&stack, 84);
    push(&stack, 29);
    push(&stack, 63);

    printStack(&stack);

    return 0;
}

void push(node **head, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = *head;

    *head = temp;
}

int pop(node **head) {
    int top;
    node *del;

    if (*head == NULL) {
        fprintf(stderr, "Stack is EMPTY\n");
        return -1;
    }

    top = (*head)->data;
    del = *head;
    (*head) = (*head)->next;
    free(del);

    return top;
}

int peek(node **head) {
    if (*head == NULL) {
        fprintf(stderr, "Stack is EMPTY\n");
        return -1;
    }

    return (*head)->data;
}

void printStack(node **head) {
    node *iter = *head;

    printf("|-Top-|\no-----o\n");
    while (iter != NULL) {
        printf("|%-5d|\n", iter->data);
        printf("o-----o\n");
        iter = iter->next;
    }
}