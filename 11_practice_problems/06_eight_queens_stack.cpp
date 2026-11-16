#include <iostream>
#include <cstdlib>
using namespace std;

// Keep the data and its operations together in one simple class.
class Stack
{
public:
    int stack[8];
    int top = -1;

    // An array is the stack: index = row, value = queen's column.
    // top is the last occupied row; -1 means the stack is empty.
    void push(int column)
    {
        top++;
        stack[top] = column;
    }

    void pop()
    {
        top--;
    }

    bool safe(int column)
    {
        int row = top + 1;
        for (int i = 0; i <= top; i++)
        {
            if (stack[i] == column) return false; // Same column.
            // On a diagonal, the row distance equals the column distance.
            if (abs(stack[i] - column) == row - i) return false;
        }
        return true;
    }

    void display()
    {
        for (int row = 0; row < 8; row++)
        {
            for (int column = 0; column < 8; column++)
            {
                if (stack[row] == column) cout << "Q ";
                else cout << ". ";
            }
            cout << endl;
        }
    }

    // Read the top value without removing it.
    int peek()
    {
        return stack[top];
    }

    bool isEmpty()
    {
        return top == -1;
    }

    int size()
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
                column = queens.peek() + 1;
                queens.pop();
            }
        }
        else
        {
            // No safe column: backtrack to the previous row.
            if (queens.isEmpty()) break; // All possibilities have been tried.
            column = queens.peek() + 1;
            queens.pop();
        }
    }
    cout << "Total solutions: " << solutions << endl;
    return 0;
}
