#include <stdio.h>
#include <stdlib.h>

// Define the structure for the linked list node
struct Node {
    int data;
    struct Node *next;
};

// Function to traverse the linked list
void traverse(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to insert a node at the beginning of the linked list
void insertAtBegin(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory not allocated\n");
        return;
    }
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Function to search for an element in the linked list
int search(struct Node *head, int data) {
    struct Node *temp = head;
    int index = 0;
    while (temp != NULL) {
        if (temp->data == data) {
            return index;
        }
        index++;
        temp = temp->next;
    }
    return -1;
}

// Function to insert a node at any index in the linked list
void insertAtAnyIndex(struct Node **head, int data, int index) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    struct Node *temp = *head;
    int i;
    for (i = 0; i < index - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to delete a node at any index in the linked list
void deleteAtAnyIndex(struct Node **head, int index) {
    struct Node *temp = *head;
    int i;
    for (i = 0; i < index - 1; i++) {
        temp = temp->next;
    }
    struct Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
}

// Function to delete a node at the end of the linked list
void deleteAtEnd(struct Node **head) {
    struct Node *temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    struct Node *nodeToDelete = temp->next;
    temp->next = NULL;
    free(nodeToDelete);
}

// Function to delete a node at the beginning of the linked list
void deleteAtBegin(struct Node **head) {
    struct Node *nodeToDelete = *head;
    *head = nodeToDelete->next;
    free(nodeToDelete);
}

// Function to reverse the linked list
void reverse(struct Node **head) {
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

// Function to create a new linked list with alternate elements
struct Node* createAlternateList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* newHead = NULL;
    struct Node* current = head;
    int position = 0;

    while (current != NULL) {
        if (position % 2 == 0) {
            // Insert at end of new list
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = current->data;
            newNode->next = NULL;

            if (newHead == NULL) {
                newHead = newNode;
            } else {
                struct Node* temp = newHead;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        position++;
        current = current->next;
    }
    return newHead;
}

int main() {
    int n;
    struct Node *head = NULL;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtBegin(&head, data);
    }
    traverse(head);
    
    // Creating alternate list
    struct Node* alternateList = createAlternateList(head);
    printf("Alternate List: ");
    traverse(alternateList);
    
    return 0;
}
