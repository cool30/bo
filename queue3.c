#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101

struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
};

// Initialize the queue
void initialize(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmpty(struct Queue* q) {
    return (q->front == -1);
}

// Check if the queue is full
int isFull(struct Queue* q) {
    return (q->rear == MAX_SIZE - 1);
}

// Enqueue (insert) an element into the queue
void enqueue(struct Queue* q, int item) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->items[q->rear] = item;
}

// Dequeue (remove) an element from the queue
int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return a sentinel value indicating an error
    }
    int removedItem = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return removedItem;
}

// Function to check if Vignesh and Lata can get money without insecurity
int canGetMoney(int N, int K) {
    struct Queue q;
    initialize(&q);

    // Insert people into the queue
    for (int i = 1; i <= N; i++) {
        enqueue(&q, i);
    }

    // Find the position of Vignesh and Lata in the queue
    int vigneshPosition = -1;
    int lataPosition = -1;
    int count = 0;

    while (!isEmpty(&q)) {
        count++;
        int person = dequeue(&q);
        if (person == K) {
            vigneshPosition = count;
        }
        if (person == K + 1) {
            lataPosition = count;
        }
    }

    // Check if Vignesh and Lata are in the same group
    if ((vigneshPosition - 1) / 3 == (lataPosition - 1) / 3) {
        return 1; // Vignesh and Lata are in the same group, they can get money
    } else {
        return 0; // Vignesh and Lata are in different groups, Lata will feel insecure
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, K;
        scanf("%d %d", &N, &K);

        if (canGetMoney(N, K)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}