#include <iostream>
using namespace std;

// Each matrix has at most 10 rows and 10 columns.
bool input(int a[][10], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (!(cin >> a[i][j])) return false;
    return true;
}

void display(int a[][10], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void add(int a[][10], int b[][10], int rows, int cols)
{
    int sum[10][10];
    // Addition uses the values at the same row and column.
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum[i][j] = a[i][j] + b[i][j];
    display(sum, rows, cols);
}

void multiply(int a[][10], int b[][10], int r1, int c1, int c2)
{
    int product[10][10] = {};
    // One answer cell = one row of A multiplied by one column of B.
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                product[i][j] += a[i][k] * b[k][j];
    display(product, r1, c2);
}

int main()
{
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
