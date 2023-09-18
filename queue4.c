#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct  {
    int items[MAX_SIZE];
    int top;
}Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push.\n");
        return;
    }
    stack->items[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1; // Return a sentinel value indicating an error
    }
    return stack->items[stack->top--];
}

void enqueue(Stack* stack1, Stack* stack2, int item) {
    while (!isEmpty(stack2)) {
        push(stack1, pop(stack2));
    }
    push(stack1, item);
}

int dequeue(Stack* stack1, Stack* stack2) {
    while (!isEmpty(stack1)) {
        push(stack2, pop(stack1));
    }
    if (isEmpty(stack2)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // Return a sentinel value indicating an error
    }
    return pop(stack2);
}

void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int main() {
    Stack stack1, stack2;
    initialize(&stack1);
    initialize(&stack2);

    enqueue(&stack1, &stack2, 1);
    enqueue(&stack1, &stack2, 2);
    enqueue(&stack1, &stack2, 3);

    printf("Enqueued elements into the queue:\n");
    display(&stack1);

    int dequeued = dequeue(&stack1, &stack2);
    printf("Dequeued element: %d\n", dequeued);

    printf("Remaining elements in the queue:\n");
    display(&stack1);

    return 0;
}
