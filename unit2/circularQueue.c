#include <stdio.h>
#include <stdlib.h>

// Structure for Circular Queue
typedef struct {
    int *arr;           // Array to store elements
    int front;          // Front index
    int rear;           // Rear index
    int size;           // Maximum size of queue
    int count;          // Current number of elements
} CircularQueue;

// Function to initialize the circular queue
void initQueue(CircularQueue *cq, int size) {
    cq->arr = (int *)malloc(size * sizeof(int));
    cq->size = size;
    cq->front = 0;
    cq->rear = -1;
    cq->count = 0;
}

// Function to check if queue is empty
int isEmpty(CircularQueue *cq) {
    return cq->count == 0;
}

// Function to check if queue is full
int isFull(CircularQueue *cq) {
    return cq->count == cq->size;
}

// Function to get size of queue
int getSize(CircularQueue *cq) {
    return cq->count;
}

// Function to enqueue (insert) element
void enqueue(CircularQueue *cq, int value) {
    if (isFull(cq)) {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return;
    }
    
    cq->rear = (cq->rear + 1) % cq->size;  // Circular increment of rear
    cq->arr[cq->rear] = value;
    cq->count++;
    printf("%d enqueued to queue\n", value);
}

// Function to dequeue (remove) element
int dequeue(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue Underflow! Cannot dequeue from empty queue\n");
        return -1;
    }
    
    int value = cq->arr[cq->front];
    cq->front = (cq->front + 1) % cq->size;  // Circular increment of front
    cq->count--;
    printf("%d dequeued from queue\n", value);
    return value;
}

// Function to get front element without removing it
int peek(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return cq->arr[cq->front];
}

// Function to display the queue
void display(CircularQueue *cq) {
    if (isEmpty(cq)) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Queue elements: ");
    int count = 0;
    int index = cq->front;
    
    while (count < cq->count) {
        printf("%d ", cq->arr[index]);
        index = (index + 1) % cq->size;
        count++;
    }
    printf("\n");
}

// Function to free the memory
void freeQueue(CircularQueue *cq) {
    free(cq->arr);
}

int main() {
    CircularQueue cq;
    int size = 5;  // Size of circular queue
    initQueue(&cq, size);
    
    int choice, value;
    
    do {
        printf("\nCircular Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Size\n");
        printf("6. Check if Empty\n");
        printf("7. Check if Full\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&cq, value);
                break;
                
            case 2:
                dequeue(&cq);
                break;
                
            case 3:
                value = peek(&cq);
                if (value != -1) {
                    printf("Front element is: %d\n", value);
                }
                break;
                
            case 4:
                display(&cq);
                break;
                
            case 5:
                printf("Current size of queue: %d\n", getSize(&cq));
                break;
                
            case 6:
                if (isEmpty(&cq)) {
                    printf("Queue is empty\n");
                } else {
                    printf("Queue is not empty\n");
                }
                break;
                
            case 7:
                if (isFull(&cq)) {
                    printf("Queue is full\n");
                } else {
                    printf("Queue is not full\n");
                }
                break;
                
            case 8:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
    
    // Free the allocated memory
    freeQueue(&cq);
    return 0;
}