#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the circular queue
struct Node {
    int data;
    struct Node* next;
};

// Structure for the circular queue
struct CircularQueue {
    struct Node *front, *rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the circular queue
struct CircularQueue* initializeQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if queue is empty
int isEmpty(struct CircularQueue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue (insert) element
void enqueue(struct CircularQueue* queue, int data) {
    struct Node* newNode = createNode(data);
    
    // If queue is empty
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
        newNode->next = newNode;  // Point to itself for circular nature
    } else {
        newNode->next = queue->front;  // Connect new node to front
        queue->rear->next = newNode;   // Connect last node to new node
        queue->rear = newNode;         // Update rear
    }
    printf("Enqueued: %d\n", data);
}

// Function to dequeue (remove) element
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    int data = queue->front->data;
    struct Node* temp = queue->front;
    
    // If only one node is present
    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
    }
    
    free(temp);
    return data;
}

// Function to display the queue
void display(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    
    struct Node* temp = queue->front;
    printf("Circular Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

// Main function to test the implementation
int main() {
    struct CircularQueue* queue = initializeQueue();
    int choice, data;
    
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(queue, data);
                break;
                
            case 2:
                data = dequeue(queue);
                if (data != -1)
                    printf("Dequeued: %d\n", data);
                break;
                
            case 3:
                display(queue);
                break;
                
            case 4:
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}