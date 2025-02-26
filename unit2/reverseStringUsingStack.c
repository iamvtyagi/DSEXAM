#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *arr;      // Pointer to the stack array
    int top;        // Index of the top element
    int capacity;   // Current capacity of the stack
} Stack;

// Function to initialize the stack
void initStack(Stack *stack, int capacity) {
    stack->arr = (char *)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to resize the stack when needed
void resizeStack(Stack *stack) {
    stack->capacity *= 2;
    stack->arr = (char *)realloc(stack->arr, stack->capacity * sizeof(char));
}

// Function to push a character onto the stack
void push(Stack *stack, char value) {
    if (isFull(stack)) {
        resizeStack(stack);
    }
    stack->arr[++stack->top] = value;
}

// Function to pop a character from the stack
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->arr[stack->top--];
}

// Function to reverse a string using stack
void reverseString(char *str) {
    int len = strlen(str);
    
    // Create and initialize stack
    Stack stack;
    initStack(&stack, len);
    
    // Push all characters of string to stack
    for (int i = 0; i < len; i++) {
        push(&stack, str[i]);
    }
    
    // Pop all characters from stack and put them back in string
    for (int i = 0; i < len; i++) {
        str[i] = pop(&stack);
    }
    
    // Free the stack memory
    free(stack.arr);
}

int main() {
    char str[100];
    
    // Input string from user
    printf("Enter a string to reverse: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character if present
    int len = strlen(str);
    if (str[len-1] == '\n') {
        str[len-1] = '\0';
        len--;
    }
    
    // Print original string
    printf("Original string: %s\n", str);
    
    // Reverse the string
    reverseString(str);
    
    // Print reversed string
    printf("Reversed string: %s\n", str);
    
    return 0;
}