/*
PRACTICE PROBLEM 2: MATRIX ADDITION AND MULTIPLICATION

PROBLEM:
Read two matrices using two-dimensional arrays. Add them when their sizes
match, and multiply A by B when A's columns equal B's rows.

EXAMPLE:
A = [1 2] and B = [3; 4] (a column).
A * B = [1*3 + 2*4] = [11]. Addition is not possible for these sizes.

HOW TO SOLVE:
1. Read each matrix's dimensions and elements row by row.
2. Addition: if r1 == r2 and c1 == c2, add matching cells.
3. Multiplication: if c1 == r2, make an r1 by c2 answer matrix.
4. For each answer cell, multiply a row of A by a column of B and add.
5. Print each available result, or explain why its dimensions do not fit.

VARIABLES / IMPORTANT POINTS:
i chooses the row, j chooses the column, and k moves along the shared size.
product[i][j] starts at zero because several products are added into it.
For example, product[i][j] = sum of a[i][k] * b[k][j].
Every matrix uses at most 10 rows and 10 columns.
*/

#include <iostream>
using namespace std;

// Each matrix has at most 10 rows and 10 columns.
// Fill the requested rows and columns. Return false if an element cannot be read.
bool input(int a[][10], int rows, int cols)
{
    // The outer loop chooses a row; the inner loop visits each cell of that row.
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(cin >> a[i][j])) return false;
    return true;
}

// Print one row per line so the two-dimensional shape is visible.
void display(int a[][10], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

// Called only for equal dimensions; each result cell is the sum of corresponding cells.
void add(int a[][10], int b[][10], int rows, int cols)
{
    int sum[10][10];
    // Addition uses the values at the same row and column.
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum[i][j] = a[i][j] + b[i][j];
    display(sum, rows, cols);
}

// Called only for compatible dimensions; accumulate shared-index products into each cell.
void multiply(int a[][10], int b[][10], int r1, int c1, int c2)
{
    // All cells start at 0; += then builds the dot product one term at a time.
    int product[10][10] = {};
    // One answer cell = one row of A multiplied by one column of B.
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                product[i][j] += a[i][k] * b[k][j];
    display(product, r1, c2);
}

// Read both matrices, check each operation separately, then call the permitted operations.
int main()
{
    // r1/c1 describe A, and r2/c2 describe B; dimensions are checked before indexing.
    int a[10][10], b[10][10], r1, c1, r2, c2;
    cout << "Enter rows and columns of A (1 to 10): ";
    if (!(cin >> r1 >> c1) || r1 < 1 || r1 > 10 || c1 < 1 || c1 > 10) return 0;
    cout << "Enter A elements: ";
    if (!input(a, r1, c1)) return 0;

    cout << "Enter rows and columns of B (1 to 10): ";
    if (!(cin >> r2 >> c2) || r2 < 1 || r2 > 10 || c2 < 1 || c2 > 10) return 0;
    cout << "Enter B elements: ";
    if (!input(b, r2, c2)) return 0;

    // Addition requires equal dimensions; multiplication requires c1 == r2.
    if (r1 == r2 && c1 == c2)
    {
        cout << "Addition:\n";
        add(a, b, r1, c1);
    }
    else cout << "Addition needs equal dimensions.\n";

    if (c1 == r2)
    {
        cout << "Multiplication:\n";
        multiply(a, b, r1, c1, c2);
    }
    else cout << "A columns must equal B rows.\n";
    return 0;
}
