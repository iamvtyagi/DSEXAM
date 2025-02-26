#include <stdio.h>
#include <stdlib.h>

// Define the structure for the circular linked list node
struct Node {
    int data;
    struct Node *next;
};

// Function to traverse the circular linked list
void traverse(struct Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Function to insert a node at the beginning of the circular linked list
void insertAtBegin(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory not allocated\n");
        return;
    }
    newNode->data = data;
    
    if (*head == NULL) {
        newNode->next = newNode;  // Point to itself if first node
        *head = newNode;
    } else {
        struct Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        newNode->next = *head;
        temp->next = newNode;
        *head = newNode;
    }
}

// Function to search for an element in the circular linked list
int search(struct Node *head, int data) {
    if (head == NULL) return -1;
    
    struct Node *temp = head;
    int index = 0;
    do {
        if (temp->data == data) {
            return index;
        }
        index++;
        temp = temp->next;
    } while (temp != head);
    
    return -1;
}

// Function to insert a node at any index in the circular linked list
void insertAtAnyIndex(struct Node **head, int data, int index) {
    if (index == 0) {
        insertAtBegin(head, data);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    
    struct Node *temp = *head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
        if (temp == *head) {
            printf("Index out of bounds\n");
            free(newNode);
            return;
        }
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
}

// Function to delete a node at any index in the circular linked list
void deleteAtAnyIndex(struct Node **head, int index) {
    if (*head == NULL) return;
    
    if (index == 0) {
        if ((*head)->next == *head) {
            free(*head);
            *head = NULL;
            return;
        }
        struct Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        struct Node *toDelete = *head;
        *head = (*head)->next;
        temp->next = *head;
        free(toDelete);
        return;
    }
    
    struct Node *temp = *head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
        if (temp == *head || temp->next == *head) {
            printf("Index out of bounds\n");
            return;
        }
    }
    
    struct Node *toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
}

// Function to delete a node at the end of the circular linked list
void deleteAtEnd(struct Node **head) {
    if (*head == NULL) return;
    
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }
    
    struct Node *temp = *head;
    while (temp->next->next != *head) {
        temp = temp->next;
    }
    
    struct Node *toDelete = temp->next;
    temp->next = *head;
    free(toDelete);
}

// Function to delete a node at the beginning of the circular linked list
void deleteAtBegin(struct Node **head) {
    if (*head == NULL) return;
    
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }
    
    struct Node *temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    
    struct Node *toDelete = *head;
    *head = (*head)->next;
    temp->next = *head;
    free(toDelete);
}

// Function to reverse the circular linked list
void reverse(struct Node **head) {
    if (*head == NULL) return;
    
    struct Node *prev = NULL;
    struct Node *current = *head;
    struct Node *next;
    
    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != *head);
    
    (*head)->next = prev;
    *head = prev;
}

// Function to create a new circular list with alternate elements
struct Node* createAlternateList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* newHead = NULL;
    struct Node* current = head;
    int position = 0;

    do {
        if (position % 2 == 0) {
            // Insert at end of new list
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = current->data;

            if (newHead == NULL) {
                newNode->next = newNode;  // Point to itself if first node
                newHead = newNode;
            } else {
                struct Node* temp = newHead;
                while (temp->next != newHead) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = newHead;
            }
        }
        position++;
        current = current->next;
    } while (current != head);

    return newHead;
}

int main() {
    struct Node *head = NULL;
    
    // Creating original list: 1->2->3->4->5->1(circular)
    insertAtBegin(&head, 5);
    insertAtBegin(&head, 4);
    insertAtBegin(&head, 3);
    insertAtBegin(&head, 2);
    insertAtBegin(&head, 1);
    
    printf("Original Circular List: ");
    traverse(head);
    
    // Testing insertAtAnyIndex
    printf("\nInserting 6 at index 2...\n");
    insertAtAnyIndex(&head, 6, 2);
    printf("List after insertion: ");
    traverse(head);
    
    // Testing deleteAtAnyIndex
    printf("\nDeleting node at index 2...\n");
    deleteAtAnyIndex(&head, 2);
    printf("List after deletion: ");
    traverse(head);
    
    // Creating alternate list
    struct Node* alternateList = createAlternateList(head);
    printf("\nAlternate List: ");
    traverse(alternateList);
    
    // Testing reverse
    printf("\nReversing the original list...\n");
    reverse(&head);
    printf("Reversed list: ");
    traverse(head);
    
    return 0;
}