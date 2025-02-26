#include <iostream>
using namespace std;

class TwoStacks {
    int* arr;
    int size;
    int top1, top2;

public:
    // Constructor
    TwoStacks(int n) {
        size = n;
        arr = new int[n];
        top1 = -1;        // Stack 1 left se start hogi
        top2 = n;         // Stack 2 right se start hogi
    }

    // Stack 1 me push
    void push1(int x) {
        if (top1 < top2 - 1) {   // Check jagah hai ya nahi
            arr[++top1] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }

    // Stack 2 me push
    void push2(int x) {
        if (top1 < top2 - 1) {   // Check jagah hai ya nahi
            arr[--top2] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }

    // Stack 1 se pop
    int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        } else {
            cout << "Stack Underflow\n";
            return -1;
        }
    }

    // Stack 2 se pop
    int pop2() {
        if (top2 < size) {
            return arr[top2++];
        } else {
            cout << "Stack Underflow\n";
            return -1;
        }
    }

    // Display the stacks
    void display() {
        cout << "Stack 1: ";
        for (int i = 0; i <= top1; i++)
            cout << arr[i] << " ";
        cout << "\nStack 2: ";
        for (int i = top2; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    TwoStacks ts(10);

    ts.push1(1);
    ts.push1(2);
    ts.push1(3);
    ts.push2(9);
    ts.push2(8);
    ts.push2(7);
    ts.display();

    ts.pop1();
    ts.pop2();
    ts.display();

    return 0;
}
