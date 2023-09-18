#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

// Define a structure for the circular queue
typedef struct  {
    char* data[MAX_SIZE];
    int front;
    int rear;
}CircularQueue;

void init(CircularQueue* cq) {
    cq->front = -1;
    cq->rear = -1;
}


int isEmpty(CircularQueue* cq) {
    return (cq->front == -1 && cq->rear == -1);
}


int isFull(CircularQueue* cq) {
    return ((cq->rear + 1) % MAX_SIZE == cq->front);
}


void insertcq(CircularQueue* cq, const char* item) {
    if (isFull(cq)) {
        printf("Queue is full. Cannot insert.\n");
        return;
    }

    cq->rear = (cq->rear + 1) % MAX_SIZE;
    cq->data[cq->rear] = strdup(item);

    if (cq->front == -1) {
        cq->front = cq->rear;
    }
}


void deletecq(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty. Cannot delete.\n");
        return;
    }

    free(cq->data[cq->front]);

    // if only one element in queue then after deleting reset to position to -1 i.e is Empty ohh!
    if (cq->front == cq->rear) {
        cq->front = cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % MAX_SIZE;
    }
}

// Display the circular queue
void displaycq(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = cq->front;
    do {
        printf("%s ", cq->data[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (cq->rear + 1) % MAX_SIZE);

    printf("\n");
}

int main() {
    CircularQueue cq;
    init(&cq);

    insertcq(&cq, "One");
    insertcq(&cq, "Two");
    insertcq(&cq, "Three");
    insertcq(&cq, "Four");

    printf("Queue after inserts: ");
    displaycq(&cq);

    deletecq(&cq);
    deletecq(&cq);

    printf("Queue after deletes: ");
    displaycq(&cq);

    insertcq(&cq, "Five");
    insertcq(&cq, "Six");
    insertcq(&cq, "Seven");

    printf("Queue after more inserts: ");
    displaycq(&cq);

    return 0;
}
