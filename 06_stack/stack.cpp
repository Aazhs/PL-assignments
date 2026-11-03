#include <string>
using namespace std;

const int MAX_SIZE = 100;

// Stack using an array. LIFO = Last In, First Out
// (like a pile of plates: you add and remove only from the top).
// Used by main.cpp to convert between infix, postfix and prefix.
class Stack
{
private:
    string items[MAX_SIZE];
    // Index of the top element; -1 means the stack is empty
    int top = -1;

public:
    // Add a value on top (ignored if the stack is full)
    void push(const string &value)
    {
        if (top < MAX_SIZE - 1)
        {
            // Move top up first, then store the value there
            items[++top] = value;
        }
    }

    // Remove and return the top value ("" if empty)
    string pop()
    {
        if (top == -1)
        {
            return "";
        }

        // Return the top value, then move top down
        return items[top--];
    }

    // Look at the top value without removing it
    string peek() const
    {
        if (top == -1)
        {
            return "";
        }

        return items[top];
    }

    bool isEmpty() const
    {
        return top == -1;
    }
};

// Example test input / output for infix to postfix:
// A + B * C + ( D / E ) ^ F -> ABC*+DE/F^+

//
// ABC*+DE/F^+
