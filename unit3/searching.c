#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define INDEX_SIZE 10

// Linear Search
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;  // Return index if element found
        }
    }
    return -1;  // Return -1 if element not found
}

// Binary Search (Recursive)
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        // If element is present at middle
        if (arr[mid] == key)
            return mid;
            
        // If element is smaller than mid
        if (arr[mid] > key)
            return binarySearchRecursive(arr, left, mid - 1, key);
            
        // If element is larger than mid
        return binarySearchRecursive(arr, mid + 1, right, key);
    }
    return -1;  // Element not present in array
}


// Binary Search (Iterative)
int binarySearchIterative(int arr[], int n, int key) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // If element is present at middle
        if (arr[mid] == key)
            return mid;
            
        // If element is smaller than mid
        if (arr[mid] > key)
            right = mid - 1;
            
        // If element is larger than mid
        left = mid + 1;
    }
    return -1;  // Element not present in array
}


// Function to create index table for indexed sequential search
void createIndex(int arr[], int n, int index[], int *indexSize) {
    int i;
    *indexSize = (n + INDEX_SIZE - 1) / INDEX_SIZE;  // Calculate number of index entries
    
    for (i = 0; i < *indexSize; i++) {
        index[i] = arr[i * INDEX_SIZE];  // Store first element of each block
    }
}

// Indexed Sequential Search
int indexedSequentialSearch(int arr[], int n, int key) {    
    int index[MAX_SIZE/INDEX_SIZE];
    int indexSize;
    
    // Create index table
    createIndex(arr, n, index, &indexSize);
    
    // Find the appropriate block
    int i;
    for (i = 0; i < indexSize-1; i++) {
        if (key < index[i+1])
            break;
    }
    
    // Linear search in the identified block
    int start = i * INDEX_SIZE;
    int end = (i == indexSize-1) ? n : (i+1) * INDEX_SIZE;
    
    for (i = start; i < end; i++) {
        if (arr[i] == key)
            return i;
    }
    
    return -1;  // Element not found
}

// Utility function to print array
void printArray(int arr[], int n) {
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int arr[MAX_SIZE], n, choice, key, result;
    
    printf("Enter the number of elements (max %d): ", MAX_SIZE);
    scanf("%d", &n);
    
    printf("Enter %d elements in sorted order for binary and indexed search: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    while (1) {
        printf("\n--- Searching Algorithms ---\n");
        printf("1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Indexed Sequential Search\n");
        printf("4. Display Array\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter element to search: ");
                scanf("%d", &key);
                result = linearSearch(arr, n, key);
                if (result != -1)
                    printf("Element found at index %d\n", result);
                else
                    printf("Element not found\n");
                break;
                
            case 2:
                printf("Enter element to search: ");
                scanf("%d", &key);
                result = binarySearchRecursive(arr, 0, n-1, key);
                if (result != -1)
                    printf("Element found at index %d\n", result);
                else
                    printf("Element not found\n");
                break;
                
            case 3:
                printf("Enter element to search: ");
                scanf("%d", &key);
                result = indexedSequentialSearch(arr, n, key);
                if (result != -1)
                    printf("Element found at index %d\n", result);
                else
                    printf("Element not found\n");
                break;
                
            case 4:
                printArray(arr, n);
                break;
                
            case 5:
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}