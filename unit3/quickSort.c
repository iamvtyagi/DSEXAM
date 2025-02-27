#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (using first element as pivot)
int partition(int arr[], int low, int high) {
    int pivot = arr[low];  // First element as pivot
    int i = low + 1; // Index for elements greater than pivot
    int j = high;    // Index for elements smaller than pivot

    while (i <= j) {
        while (i <= high && arr[i] <= pivot) i++; // Move i forward
        while (j >= low && arr[j] > pivot) j--;   // Move j backward

        if (i < j) { // Swap if i and j haven't crossed
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]); // Swap pivot to correct position
    return j;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partition index

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}