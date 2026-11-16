#include <iostream>
#include <cstdlib>
using namespace std;

// An array is the stack: index = row, value = queen's column.
// top is the last occupied row; -1 means the stack is empty.
void push(int stack[], int& top, int column)
{
    top++;
    stack[top] = column;
}

void pop(int& top)
{
    top--;
}

bool safe(int stack[], int top, int column)
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

void display(int stack[])
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

int main()
{
    int stack[8], top = -1, column = 0, solutions = 0;
    while (true)
    {
        // Try columns from left to right in the next empty row.
        while (column < 8 && !safe(stack, top, column)) column++;
        if (column < 8)
        {
            push(stack, top, column);
            column = 0; // Start the next row at its first column.
            if (top == 7)
            {
                solutions++; // All eight queens have been placed safely.
                if (solutions == 1)
                {
                    cout << "First solution:\n";
                    display(stack);
                }
                // Remove the last queen and look for another solution.
                column = stack[top] + 1;
                pop(top);
            }
        }
        else
        {
            // No safe column: backtrack to the previous row.
            if (top == -1) break; // All possibilities have been tried.
            column = stack[top] + 1;
            pop(top);
        }
    }
    cout << "Total solutions: " << solutions << endl;
    return 0;
}
