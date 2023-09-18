#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct  {
    int items[MAX_SIZE];
    int front;
    int rear;
}CircularQueue;

// Initialize the circular queue
void initialize(CircularQueue* cq) {
    cq->front = -1;
    cq->rear = -1;
}

// Check if the circular queue is empty
int isEmpty(CircularQueue* cq) {
    return (cq->front == -1 && cq->rear == -1);
}

// Check if the circular queue is full
int isFull(CircularQueue* cq) {
    return ((cq->rear + 1) % MAX_SIZE == cq->front);
}

// Insert an element into the circular queue
void insertcq(CircularQueue* cq, int item) {
    if (isFull(cq)) {
        printf("Queue is full. Cannot insert.\n");
        return;
    }

    if (isEmpty(cq)) {
        cq->front = cq->rear = 0;
    } else {
        cq->rear = (cq->rear + 1) % (MAX_SIZE / 2);
    }

    cq->items[cq->rear] = item;
}

// Delete an element from the circular queue
int deletecq(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty. Cannot delete.\n");
        return -1; // Return a value indicating an error
    }

    int deletedItem = cq->items[cq->front];

    if (cq->front == cq->rear) {
        cq->front = cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % (MAX_SIZE / 2);
    }

    return deletedItem;
}

// Display the circular queue
void displaycq(CircularQueue* cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = cq->front;
    do {
        printf("%d ", cq->items[i]);
        i = (i + 1) % (MAX_SIZE / 2);
    } while (i != (cq->rear + 1) % (MAX_SIZE / 2));

    printf("\n");
}

int main() {
    CircularQueue cq1, cq2;
    initialize(&cq1);
    initialize(&cq2);

    // Insert elements into the first queue (0 to N/2)
    for (int i = 0; i <= MAX_SIZE / 4; i++) {
        insertcq(&cq1, i);
    }

    // Insert elements into the second queue (N/2+1 to N-1)
    for (int i = MAX_SIZE / 2 + 1; i < MAX_SIZE; i++) {
        insertcq(&cq2, i);
    }

    printf("First Queue: ");
    displaycq(&cq1);

    printf("Second Queue: ");
    displaycq(&cq2);

    deletecq(&cq1);
    deletecq(&cq2);
    deletecq(&cq2);

    printf("\nFirst Queue after deleting is: ");
    displaycq(&cq1);

    printf("Second Queue after deleting is: ");
    displaycq(&cq2);

    insertcq(&cq1, 100);
    insertcq(&cq2, 100);

    printf("\nFirst Queue after inserting is: ");
    displaycq(&cq1);

    printf("Second Queue after inserting is: ");
    displaycq(&cq2);

    insertcq(&cq1, 100);
    insertcq(&cq2, 100);
    insertcq(&cq1, 100);
    insertcq(&cq2, 100);

    // overflow occurring consition
    insertcq(&cq1, 100);
    insertcq(&cq2, 100);
    printf("\nFirst Queue after inserting is: ");
    displaycq(&cq1);

    printf("Second Queue after inserting is: ");
    displaycq(&cq2);
    
    return 0;
}
