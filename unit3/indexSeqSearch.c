#include <stdio.h>

// Structure to store index table
typedef struct {
    int key;
    int position;
} IndexEntry;

// Function to perform sequential search within a block
int sequentialSearch(int arr[], int start, int end, int key) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == key)
            return i;  // Element found
    }
    return -1; // Element not found
}

// Function to perform index sequential search
int indexSequentialSearch(int arr[], IndexEntry indexTable[], int indexSize, int n, int key) {
    // Step 1: Search in index table
    int blockStart = 0, blockEnd = 0;

    for (int i = 0; i < indexSize; i++) {
        if (indexTable[i].key > key)
            break;
        blockStart = indexTable[i].position;
    }

    // Define block end
    blockEnd = (blockStart + 4 < n) ? (blockStart + 4) : (n - 1);

    // Step 2: Perform sequential search in the identified block
    return sequentialSearch(arr, blockStart, blockEnd, key);
}

// Main function
int main() {
    int arr[] = {3, 8, 12, 17, 24, 29, 33, 39, 42, 47, 51, 55};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Index Table (first element of each block and position)
    IndexEntry indexTable[] = {
        {3, 0}, {24, 4}, {42, 8}  // Example index table (block size = 4)
    };
    int indexSize = sizeof(indexTable) / sizeof(indexTable[0]);

    int key = 39;
    int result = indexSequentialSearch(arr, indexTable, indexSize, n, key);

    if (result != -1)
        printf("Element %d found at index %d\n", key, result);
    else
        printf("Element %d not found\n", key);

    return 0;
}
