#include <iostream>
#include <cstdlib>
using namespace std;

// Adapted from PL/stack/stack.cpp: store integer queen columns.
const int MAX_SIZE = 8;
class Stack
{
private:
    int items[MAX_SIZE];
    int top = -1;

public:
    // Same push/pop/peek operations as stack/stack.cpp.
    void push(int value)
    {
        if (top < MAX_SIZE - 1)
        {
            items[++top] = value;
        }
    }

    int pop()
    {
        if (top == -1)
        {
            return -1;
        }

        return items[top--];
    }

    int peek() const
    {
        if (top == -1)
        {
            return -1;
        }

        return items[top];
    }

    bool isEmpty() const
    {
        return top == -1;
    }
    bool safe(int column)
    {
        int row = top + 1;
        for (int i = 0; i <= top; i++)
        {
            if (items[i] == column) return false; // Same column.
            // On a diagonal, the row distance equals the column distance.
            if (abs(items[i] - column) == row - i) return false;
        }
        return true;
    }

    void display()
    {
        for (int row = 0; row < 8; row++)
        {
            for (int column = 0; column < 8; column++)
            {
                if (items[row] == column) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
    }

    int size() const
    {
        return top + 1;
    }
};

int main()
{
    Stack queens;
    int column = 0, solutions = 0;
    while (true)
    {
        // Try columns from left to right in the next empty row.
        while (column < 8 && !queens.safe(column)) column++;
        if (column < 8)
        {
            queens.push(column);
            column = 0; // Start the next row at its first column.
            if (queens.size() == 8)
            {
                solutions++; // All eight queens have been placed safely.
                if (solutions == 1)
                {
                    cout << "First solution:\n";
                    queens.display();
                }
                // Remove the last queen and look for another solution.
                column = queens.pop() + 1;
            }
        }
        else
        {
            // No safe column: backtrack to the previous row.
            if (queens.isEmpty()) break; // All possibilities have been tried.
            column = queens.pop() + 1;
        }
    }
    cout << "Total solutions: " << solutions << endl;
    return 0;
}
