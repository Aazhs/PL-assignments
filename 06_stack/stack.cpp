#include <string>
using namespace std;

const int MAX_SIZE = 100;

class Stack
{
private:
    string items[MAX_SIZE];
    // Index of the top element; -1 means the stack is empty
    int top = -1;

public:
    void push(const string &value)
    {
        if (top < MAX_SIZE - 1)
        {
            // Move top up first, then store the value there
            items[++top] = value;
        }
    }

    string pop()
    {
        if (top == -1)
        {
            return "";
        }

        // Return the top value, then move top down
        return items[top--];
    }

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

// A + B * C + ( D / E ) ^ F -> ABC*+DE/F^+

//
// ABC*+DE/F^+
