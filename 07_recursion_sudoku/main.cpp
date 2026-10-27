#include <iostream>
using namespace std;

// 4x4 sudoku: digits 1 to 4, each row, column and 2x2 box has every digit once.
// Empty cells are 0.
const int N = 4;

bool isSafe(int grid[N][N], int row, int col, int num) {
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
