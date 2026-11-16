#include <iostream>
#include <cstdlib>
using namespace std;

// How this program works:
// Place one queen per row. Two queens cannot share a column or diagonal.
// Push a safe column onto the stack to move to the next row.
// If no column works, pop the previous queen and try her next column.
// This is backtracking using a stack, without recursive calls.

// Stack index = row, stored value = the column occupied by that queen.
class Stack{
public:
    int column[8], top = -1;
    void push(int col){ column[++top] = col; }
    void pop(){ top--; }
    bool safe(int col){
        int row = top + 1; // We are testing a queen in the next empty row.
        // Equal column means a vertical attack. Equal distances mean a diagonal attack.
        for(int i = 0; i <= top; i++){
            if(column[i] == col || abs(column[i] - col) == row - i) return false;
        }
        return true;
    }
};
// Program starts here: run the algorithm and display its result.
int main(){
    Stack queens;
    int col = 0, solutions = 0;
    // Iterative backtracking: pop to retry the previous row when stuck.
    while(true){
        while(col < 8 && !queens.safe(col)) col++;
        if(col < 8){
            // A safe position is found. Start the next row from column 0.
            queens.push(col);
            col = 0;
            if(queens.top == 7){
                solutions++;
                if(solutions == 1){
                    cout << "First solution:\n";
                    for(int row = 0; row < 8; row++){
                        for(int c = 0; c < 8; c++) cout << (queens.column[row] == c ? "Q " : ". ");
                        cout << "\n";
                    }
                }
                // Retry the previous row at the column after its old queen.
                col = queens.column[queens.top] + 1;
                queens.pop();
            }
        }
        else{
            if(queens.top == -1) break;
            // Retry the previous row at the column after its old queen.
            col = queens.column[queens.top] + 1;
            queens.pop();
        }
    }
    cout << "Total solutions: " << solutions << "\n";
}
