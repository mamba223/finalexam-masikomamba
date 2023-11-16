#include <iostream>

using namespace std;

class MyStack {
private:
    int* stack;
    int itop;
    int capacity;

public:
    MyStack();
    ~MyStack(); // Destructor to free the dynamically allocated memory.
    void push(int x);
    void pop();
    int top();
    int Ssize();
};

MyStack::MyStack() {
    capacity = 2; // Initial capacity
    stack = new int[capacity];
    itop = -1;
}

MyStack::~MyStack() {
    delete[] stack;
}

void MyStack::push(int x) {
    // Check if the current top index (itop) is greater than or equal to the size of the stack.
    if (itop >= capacity - 1) {
        // The stack is full, so we need to resize it.
        int newSize = (capacity == 0) ? 2 : 2 * capacity; // Double the size or start with 2 if empty.

        // Create a new stack with the new size.
        int* stack_new = new int[newSize];

        // Copy elements from the old stack to the new stack.
        for (int i = 0; i <= itop; i++) {
            stack_new[i] = stack[i];
        }

        // Deallocate the memory of the old stack.
        delete[] stack;

        // Update the stack pointer and size.
        stack = stack_new;
        capacity = newSize;
    }

    // Add x to the top of the stack and update itop.
    stack[++itop] = x;
}

void MyStack::pop() {
    if (itop >= 0 && stack != nullptr) {
        // If the stack is not empty, simply decrement the top index.
        itop--;
    }
    // Note: We don't need to deallocate memory here since we're using an array with dynamic resizing.
}

int MyStack::top() {
    if (itop >= 0 && stack != nullptr) {
        return stack[itop];
    }
    return -1; // Stack is empty
}

int MyStack::Ssize() {
    return itop + 1;
}

int main() {
    MyStack x;
    int temp;
    int input_size = 0; // Variable to store the size of input
    while (cin >> temp) {
        x.push(temp);
        input_size++;
    }

    // Use input_size as the stopping condition
    for (int i = 0; i < input_size; i++) {
        cout << x.top() << '\n';
        x.pop();
    }

    return 0;
}
