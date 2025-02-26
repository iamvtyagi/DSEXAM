#include <stdio.h>
#include <stdlib.h>

// Define the structure for the doubly linked list node
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

// Function to traverse the doubly linked list
void traverse(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to traverse the doubly linked list in reverse
void reverseTraverse(struct Node *head) {
    if (head == NULL) return;
    
    // Go to the last node
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Print from last to first
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Function to insert a node at the beginning of the doubly linked list
void insertAtBegin(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory not allocated\n");
        return;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = *head;
    
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to search for an element in the doubly linked list
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

// Function to insert a node at any index in the doubly linked list
void insertAtAnyIndex(struct Node **head, int data, int index) {
    if (index == 0) {
        insertAtBegin(head, data);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    
    struct Node *temp = *head;
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Index out of bounds\n");
        free(newNode);
        return;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Function to delete a node at any index in the doubly linked list
void deleteAtAnyIndex(struct Node **head, int index) {
    if (*head == NULL) return;
    
    struct Node *temp = *head;
    
    if (index == 0) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }
    
    for (int i = 0; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Index out of bounds\n");
        return;
    }
    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    free(temp);
}

// Function to delete a node at the end of the doubly linked list
void deleteAtEnd(struct Node **head) {
    if (*head == NULL) return;
    
    struct Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head = NULL;
    }
    
    free(temp);
}

// Function to delete a node at the beginning of the doubly linked list
void deleteAtBegin(struct Node **head) {
    if (*head == NULL) return;
    
    struct Node *temp = *head;
    *head = temp->next;
    
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    
    free(temp);
}

// Function to reverse the doubly linked list
void reverse(struct Node **head) {
    struct Node *temp = NULL;
    struct Node *current = *head;
    
    while (current != NULL) {
        // Swap next and prev pointers
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        
        // Move to next node
        current = current->prev;
    }
    
    // Update head
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// Function to create a new list with alternate elements
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
            newNode->prev = NULL;

            if (newHead == NULL) {
                newHead = newNode;
            } else {
                struct Node* temp = newHead;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->prev = temp;
            }
        }
        position++;
        current = current->next;
    }
    return newHead;
}

int main() {
    struct Node *head = NULL;
    
    // Creating original list: 1->2->3->4->5
    insertAtBegin(&head, 5);
    insertAtBegin(&head, 4);
    insertAtBegin(&head, 3);
    insertAtBegin(&head, 2);
    insertAtBegin(&head, 1);
    
    printf("Original List (forward): ");
    traverse(head);
    
    printf("Original List (reverse): ");
    reverseTraverse(head);
    
    // Creating alternate list
    struct Node* alternateList = createAlternateList(head);
    printf("\nAlternate List (forward): ");
    traverse(alternateList);
    printf("Alternate List (reverse): ");
    reverseTraverse(alternateList);
    
    return 0;
}