/*
PRACTICE PROBLEM 6: EIGHT QUEENS USING A STACK

PROBLEM:
Place eight queens on an 8 by 8 chessboard so that no two attack each other.
Use an explicit stack for backtracking. Print one board and count all solutions.

EXAMPLE:
A valid set of columns for rows 0 to 7 is: 0 4 7 5 2 6 1 3.
Q marks a queen and . marks an empty square. There are 92 solutions in total.

HOW TO SOLVE:
1. Place one queen in each row; the stack stores the chosen column per row.
2. Try columns 0 through 7 in the next empty row.
3. safe() rejects a column shared with an older queen or on her diagonal.
4. Push a safe column and start the next row at column 0.
5. If a row has no safe column, pop the previous queen and try her next column.
6. When eight queens are placed, count the solution and continue backtracking.
7. Stop when the stack is empty and no first-row choice remains.

VARIABLES / IMPORTANT POINTS:
items[row] = queen column; top = last occupied row; -1 = empty stack.
Row attacks are avoided automatically by placing one queen per row.
A diagonal attack has abs(column difference) == row difference.
pop() returns the old column so the search can continue just after it.
*/

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
    // Store a new queen column one slot above top, unless all eight slots are occupied.
    void push(int value)
    {
        if (top < MAX_SIZE - 1)
        {
            // Increase top first, then store the new column at that stack position.
            items[++top] = value;
        }
    }

    // Return and remove the most recent queen column; -1 means the stack was empty.
    int pop()
    {
        if (top == -1)
        {
            return -1;
        }

        // Read the old top value before reducing top; the caller uses it to try the next column.
        return items[top--];
    }

    // Read the most recent column without removing it; -1 means there is no queen.
    int peek() const
    {
        if (top == -1)
        {
            return -1;
        }

        return items[top];
    }

    // top == -1 represents a stack containing no queens.
    bool isEmpty() const
    {
        return top == -1;
    }
    // Compare a candidate against every placed queen for column and diagonal attacks.
    bool safe(int column)
    {
        // Rows 0..top already contain queens, so this candidate belongs in row top+1.
        int row = top + 1;
        for (int i = 0; i <= top; i++)
        {
            // Each stack entry belongs to a different row; this test rules out a shared column.
            if (items[i] == column) return false; // Same column.
            // On a diagonal, the row distance equals the column distance.
            if (abs(items[i] - column) == row - i) return false;
        }
        return true;
    }

    // For each board cell print Q at the stored column, otherwise print an empty square.
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

    // Since top is a zero-based index, the number of stored columns is top + 1.
    int size() const
    {
        return top + 1;
    }
};

// Perform iterative backtracking with the stack, display the first board, and count all boards.
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
            // Reaching eight stored columns means every row has a queen and all checks passed.
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
