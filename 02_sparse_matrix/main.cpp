#include <iostream>

using namespace std;

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
const int MAX_NON_ZERO = 400;

class Triplet {
public:
  // Row 0 is the header {rows, cols, non-zero count}; rows 1..n are {row, col, value}
  int triplet[MAX_NON_ZERO + 1][3];
  int totalRows;

  Triplet();

  void displayTriplet();
  void inputTriplet();
  void inputSparseAndConvert();
  void sparseToTriplet(int sparse[MAX_ROWS][MAX_COLS], int rowCount,
                      int colCount);
  Triplet addTriplet(Triplet other);
  Triplet transposeSimple();
  Triplet transposeFast();
  Triplet multiplyTriplet(Triplet other);
};

Triplet::Triplet() {
  totalRows = 1;
  triplet[0][0] = 0;
  triplet[0][1] = 0;
  triplet[0][2] = 0;
}

void Triplet::displayTriplet() {
  cout << "Triplet matrix:\n";
  for (int i = 0; i < totalRows; i++) {
    cout << triplet[i][0] << " " << triplet[i][1] << " " << triplet[i][2]
         << "\n";
  }
}

void Triplet::inputTriplet() {
  int rowCount, colCount, nonZeroCount;

  cout << "Enter rows cols non_zero: ";
  cin >> rowCount >> colCount >> nonZeroCount;

  if (rowCount <= 0 || colCount <= 0 || rowCount > MAX_ROWS ||
      colCount > MAX_COLS || nonZeroCount < 0 || nonZeroCount > MAX_NON_ZERO) {
    cout << "Invalid size. Max rows=" << MAX_ROWS << ", cols=" << MAX_COLS
         << "\n";
    return;
  }

  triplet[0][0] = rowCount;
  triplet[0][1] = colCount;
  triplet[0][2] = nonZeroCount;
  totalRows = nonZeroCount + 1;

  cout << "Enter each non-zero as: row col value (0-based index)\n";
  for (int i = 1; i <= nonZeroCount; i++) {
    cin >> triplet[i][0] >> triplet[i][1] >> triplet[i][2];
  }
}

void Triplet::inputSparseAndConvert() {
  int sparse[MAX_ROWS][MAX_COLS];
  int rowCount, colCount;

  cout << "Enter rows cols: ";
  cin >> rowCount >> colCount;

  if (rowCount <= 0 || colCount <= 0 || rowCount > MAX_ROWS ||
      colCount > MAX_COLS) {
    cout << "Invalid size. Max rows=" << MAX_ROWS << ", cols=" << MAX_COLS
         << "\n";
    return;
  }

  cout << "Enter sparse matrix values:\n";
  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      cin >> sparse[i][j];
    }
  }

  sparseToTriplet(sparse, rowCount, colCount);
}

void Triplet::sparseToTriplet(int sparse[MAX_ROWS][MAX_COLS], int rowCount,
                              int colCount) {
  int next = 1;
  int nonZeroCount = 0;

  triplet[0][0] = rowCount;
  triplet[0][1] = colCount;
  triplet[0][2] = 0;

  for (int i = 0; i < rowCount; i++) {
    for (int j = 0; j < colCount; j++) {
      if (sparse[i][j] != 0) {
        triplet[next][0] = i;
        triplet[next][1] = j;
        triplet[next][2] = sparse[i][j];
        next++;
        nonZeroCount++;
      }
    }
  }

  triplet[0][2] = nonZeroCount;
  totalRows = nonZeroCount + 1;
}

Triplet Triplet::addTriplet(Triplet other) {
  Triplet result;

  if (triplet[0][0] != other.triplet[0][0] ||
      triplet[0][1] != other.triplet[0][1]) {
    cout << "Add not possible. Size must be same.\n";
    return result;
  }

  int n1 = triplet[0][2];
  int n2 = other.triplet[0][2];
  int i = 1;
  int j = 1;
  int k = 1;

  result.triplet[0][0] = triplet[0][0];
  result.triplet[0][1] = triplet[0][1];

  // Merge like in merge sort: both lists are sorted by (row, col), so copy the one
  // that comes first in the matrix
  while (i <= n1 && j <= n2) {
    int r1 = triplet[i][0];
    int c1 = triplet[i][1];
    int r2 = other.triplet[j][0];
    int c2 = other.triplet[j][1];

    if (r1 < r2 || (r1 == r2 && c1 < c2)) {
      result.triplet[k][0] = triplet[i][0];
      result.triplet[k][1] = triplet[i][1];
      result.triplet[k][2] = triplet[i][2];
      i++;
      k++;
    } else if (r2 < r1 || (r1 == r2 && c2 < c1)) {
      result.triplet[k][0] = other.triplet[j][0];
      result.triplet[k][1] = other.triplet[j][1];
      result.triplet[k][2] = other.triplet[j][2];
      j++;
      k++;
    } else {
      // Same position in both matrices: add the values, and skip the entry if they cancel to 0
      int sum = triplet[i][2] + other.triplet[j][2];
      if (sum != 0) {
        result.triplet[k][0] = r1;
        result.triplet[k][1] = c1;
        result.triplet[k][2] = sum;
        k++;
      }
      i++;
      j++;
    }
  }

  // Copy whatever is left over in either matrix
  while (i <= n1) {
    result.triplet[k][0] = triplet[i][0];
    result.triplet[k][1] = triplet[i][1];
    result.triplet[k][2] = triplet[i][2];
    i++;
    k++;
  }

  while (j <= n2) {
    result.triplet[k][0] = other.triplet[j][0];
    result.triplet[k][1] = other.triplet[j][1];
    result.triplet[k][2] = other.triplet[j][2];
    j++;
    k++;
  }

  result.triplet[0][2] = k - 1;
  result.totalRows = k;
  return result;
}

Triplet Triplet::transposeSimple() {
  Triplet result;
  int rowCount = triplet[0][0];
  int colCount = triplet[0][1];
  int nonZeroCount = triplet[0][2];

  result.triplet[0][0] = colCount;
  result.triplet[0][1] = rowCount;
  result.triplet[0][2] = nonZeroCount;
  result.totalRows = nonZeroCount + 1;

  // Go column by column; each element of column 'col' becomes an element of row 'col'
  // in the result, so the result comes out already sorted by row
  int next = 1;
  for (int col = 0; col < colCount; col++) {
    for (int i = 1; i <= nonZeroCount; i++) {
      if (triplet[i][1] == col) {
        result.triplet[next][0] = triplet[i][1];
        result.triplet[next][1] = triplet[i][0];
        result.triplet[next][2] = triplet[i][2];
        next++;
      }
    }
  }

  return result;
}

Triplet Triplet::transposeFast() {
  Triplet result;
  int rowCount = triplet[0][0];
  int colCount = triplet[0][1];
  int nonZeroCount = triplet[0][2];

  result.triplet[0][0] = colCount;
  result.triplet[0][1] = rowCount;
  result.triplet[0][2] = nonZeroCount;
  result.totalRows = nonZeroCount + 1;

  // totalInCol[c] = number of non-zero elements in column c
  int totalInCol[MAX_COLS] = {0};
  int startIndex[MAX_COLS] = {0};

  for (int i = 1; i <= nonZeroCount; i++) {
    totalInCol[triplet[i][1]]++;
  }

  // startIndex[c] = where column c's elements start in the result
  // (each column starts right after all the elements of the previous columns)
  startIndex[0] = 1;
  for (int i = 1; i < colCount; i++) {
    startIndex[i] = startIndex[i - 1] + totalInCol[i - 1];
  }

  // Put each element straight into its slot, then move that column's slot forward by one
  for (int i = 1; i <= nonZeroCount; i++) {
    int col = triplet[i][1];
    int pos = startIndex[col];

    result.triplet[pos][0] = triplet[i][1];
    result.triplet[pos][1] = triplet[i][0];
    result.triplet[pos][2] = triplet[i][2];

    startIndex[col]++;
  }

  return result;
}

Triplet Triplet::multiplyTriplet(Triplet other) {
  Triplet result;

  if (triplet[0][1] != other.triplet[0][0]) {
    cout << "Multiplication not possible. Matrix 1 columns must equal Matrix 2 "
            "rows.\n";
    return result;
  }

  // Use a normal 2D array to add up the products: A[i][k] * B[k][j] goes into product[i][j]
  int product[MAX_ROWS][MAX_COLS] = {};

  for (int i = 1; i <= triplet[0][2]; i++) {
    for (int j = 1; j <= other.triplet[0][2]; j++) {
      // Only multiply when A's column equals B's row (the common 'k')
      if (triplet[i][1] == other.triplet[j][0]) {
        product[triplet[i][0]][other.triplet[j][1]] +=
            triplet[i][2] * other.triplet[j][2];
      }
    }
  }

  // Convert the full product matrix back into triplet form
  result.sparseToTriplet(product, triplet[0][0], other.triplet[0][1]);
  return result;
}

#include <limits>

int main() {
  Triplet firstMatrix;

  while (true) {
    int choice;
    cout << "\n1.Input Triplet\n";
    cout << "2.Input Sparse and Convert\n";
    cout << "3.Display Triplet\n";
    cout << "4.Add Another Triplet\n";
    cout << "5.Transpose (Simple)\n";
    cout << "6.Transpose (Fast)\n";
    cout << "7.Multiply Another Triplet\n";
    cout << "8.Exit\n";
    cout << "Enter choice: ";

    // Non-number entered: clear the error state and throw away the bad input
    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Please enter a number from 1 to 8.\n";
      continue;
    }
    // Throw away the rest of the line so it doesn't affect the next input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      firstMatrix.inputTriplet();
      break;
    case 2:
      firstMatrix.inputSparseAndConvert();
      break;
    case 3:
      firstMatrix.displayTriplet();
      break;
    case 4: {
      Triplet secondMatrix;
      cout << "Input second matrix in triplet form:\n";
      secondMatrix.inputTriplet();
      Triplet result = firstMatrix.addTriplet(secondMatrix);
      cout << "Added triplet:\n";
      result.displayTriplet();
      break;
    }
    case 5: {
      Triplet result = firstMatrix.transposeSimple();
      cout << "Transpose by simple method:\n";
      result.displayTriplet();
      break;
    }
    case 6: {
      Triplet result = firstMatrix.transposeFast();
      cout << "Transpose by fast method:\n";
      result.displayTriplet();
      break;
    }
    case 7: {
      Triplet secondMatrix;
      cout << "Input second matrix in triplet form:\n";
      secondMatrix.inputTriplet();
      Triplet result = firstMatrix.multiplyTriplet(secondMatrix);
      cout << "Multiplied triplet:\n";
      result.displayTriplet();
      break;
    }
    case 8:
      return 0;
    default:
      cout << "Wrong choice\n";
      break;
    }
  }

  return 0;
}
