#include <iostream>
using namespace std;

// 4x4 sudoku: digits 1 to 4, each row, column and 2x2 box has every digit once.
// Empty cells are 0.
// Method: recursion + backtracking. Fill cells one by one; if we get stuck,
// go back to the previous cell and try a different digit.
const int N = 4;

// Can 'num' be placed at (row, col)? Only if it is not already in
// the same row, the same column, or the same 2x2 box.
bool isSafe(int grid[N][N], int row, int col, int num) {
    // grid[row][i] checks the row, grid[i][col] checks the column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Top-left corner of the 2x2 box that contains (row, col)
    int boxRow = row - row % 2;
    int boxCol = col - col % 2;
    for (int i = boxRow; i < boxRow + 2; i++) {
        for (int j = boxCol; j < boxCol + 2; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}


// Try to fill the grid starting from cell (row, col), moving left to right,
// top to bottom. Returns true if the whole grid could be filled.
bool solve(int grid[N][N], int row, int col) {

    // Went past the last row, so every cell has been filled
    if (row == N) {
        return true;
    }


    // Next cell to fill: move right, or go to the start of the next row
    int nextRow = (col == N - 1) ? row + 1 : row;
    int nextCol = (col == N - 1) ? 0 : col + 1;

    if (grid[row][col] != 0) {
        // Given number: skip it and move on
        return solve(grid, nextRow, nextCol);
    }

    // Try every digit that fits here and recurse to fill the rest of the grid
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid, nextRow, nextCol)) {
                return true;
            }
            grid[row][col] = 0;  // backtrack: undo and try the next digit
        }
    }
    return false;  // no digit works here
}

int main() {
    int grid[N][N];

    cout << "Enter " << N * N << " numbers (0 for an empty cell, 1-" << N << " otherwise):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    // Start solving from the top-left cell
    if (solve(grid, 0, 0)) {
        cout << "\nSolution:\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
