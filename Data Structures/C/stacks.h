/* Notice how these stack operations are similar to the functions in singly_ll.c like inserting by head but rather 
   than having a return type (we are using void so there's no return type) we just transfer the memory address of 
   the node/LL (AKA the pointer of the node/LL) through the parameter. This is to demonstrate the different ways 
   to interact with structs in memory. */

// struct definitions
typedef struct node node;

struct node {
    int data;
    node *next;
};

// prototypes / main stack operations
void push(node **head, int data);
int pop(node **head);
int peek(node **head);
void freeStack(node **stack);
void printStack(node **head);

// push new data into the stack (gets inserted at the head of the linked list therefore following LIFO principle)
void push(node **head, int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = *head;

    *head = temp;
}

// pop the top most variable/data from the stack
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

// return the value of the top most variable in the stack, if its empty, return -1
int peek(node **head) {
    if (*head == NULL) {
        fprintf(stderr, "Stack is EMPTY\n");
        return -1;
    }

    return (*head)->data;
}

// print the entirety of the stack in the form of a stack
void printStack(node **head) {
    node *iter = *head;

    printf("|-Top-|\no-----o\n");
    while (iter != NULL) {
        printf("|%-5d|\n", iter->data);
        printf("o-----o\n");
        iter = iter->next;
    }
}

void freeStack(node **stack) {
    node *temp = *stack;
    node *iter = NULL;
    while (temp != NULL) {
        iter = temp->next;
        free(temp);
        temp = iter;
    }
}