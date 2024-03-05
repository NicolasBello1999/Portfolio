typedef struct node node;
typedef struct queue queue;

struct node {
    int data;
    node *next;
};

struct queue {
    int size;
    node *front;
};

node *createNode(int data) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;

    return temp;
}

void initiateQueue(queue **q) {
    (*q)->size = 0;
    (*q)->front = NULL;
}

void enqueue(queue **q, int data) {
    node *temp = createNode(data);

    if ((*q)->size == 0) {
        (*q)->front = temp;
    } else {
        node *iter = (*q)->front;
        while (iter->next != NULL)
            iter = iter->next;
        iter->next = temp;
    }
    (*q)->size++;
}

void dequeue(queue **q) {
    if ((*q)->size == 0) {
        printf("Queue is empty...\n");
        return;
    }

    node *temp = (*q)->front;
    (*q)->front = temp->next;

    free(temp);
    (*q)->size--;
}

node *front(queue *q) {
    return q->front;
}