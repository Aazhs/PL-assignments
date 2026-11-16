#include <iostream>
using namespace std;

// How this program works:
// Addition: add values at matching row/column positions.
// Multiplication: result[i][j] = sum of A[i][k] * B[k][j].
// Example: [1 2] multiplied by column [3 4] gives 1*3 + 2*4 = 11.

// A matrix uses row and column indices in a two-dimensional array.
class Matrix{
public:
    long long data[10][10] = {};
    int rows = 0, cols = 0;
    bool input(){
        cout << "Enter rows and columns (1 to 10): ";
        if(!(cin >> rows >> cols) || rows < 1 || rows > 10 || cols < 1 || cols > 10) return false;
        cout << "Enter elements row by row: ";
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) if(!(cin >> data[i][j])) return false;
        return true;
    }
    void display(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++) cout << data[i][j] << " ";
            cout << "\n";
        }
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    Matrix a, b;
    cout << "Matrix A:\n";
    if(!a.input()) return 0;
    cout << "Matrix B:\n";
    if(!b.input()) return 0;
    int choice;
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Matrix Menu =====\n1. Addition\n2. Multiplication (A * B)\n3. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 3) break;
        Matrix result;
        if(choice == 1){
            if(a.rows != b.rows || a.cols != b.cols){
                cout << "Addition needs equal dimensions.\n";
                continue;
            }
            result.rows = a.rows; result.cols = a.cols;
            for(int i = 0; i < a.rows; i++)
                for(int j = 0; j < a.cols; j++) result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
        else if(choice == 2){
            if(a.cols != b.rows){
                cout << "A columns must equal B rows.\n";
                continue;
            }
            result.rows = a.rows; result.cols = b.cols;
            // Each result cell is a dot product of one row and one column.
            for(int i = 0; i < a.rows; i++)
                for(int j = 0; j < b.cols; j++)
                    for(int k = 0; k < a.cols; k++) result.data[i][j] += a.data[i][k] * b.data[k][j];
        }
        else{ cout << "Invalid choice.\n"; continue; }
        result.display();
    }
}
