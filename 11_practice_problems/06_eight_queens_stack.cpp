#include <iostream>
#include <cstdlib>
using namespace std;

// Stack index = row, stored value = the column occupied by that queen.
class Stack{
public:
    int column[8], top = -1;
    void push(int col){ column[++top] = col; }
    void pop(){ top--; }
    bool safe(int col){
        int row = top + 1;
        for(int i = 0; i <= top; i++){
            if(column[i] == col || abs(column[i] - col) == row - i) return false;
        }
        return true;
    }
};
int main(){
    Stack queens;
    int col = 0, solutions = 0;
    // Iterative backtracking: pop to retry the previous row when stuck.
    while(true){
        while(col < 8 && !queens.safe(col)) col++;
        if(col < 8){
            queens.push(col); col = 0;
            if(queens.top == 7){
                solutions++;
                if(solutions == 1){
                    cout << "First solution:\n";
                    for(int row = 0; row < 8; row++){
                        for(int c = 0; c < 8; c++) cout << (queens.column[row] == c ? "Q " : ". ");
                        cout << "\n";
                    }
                }
                col = queens.column[queens.top] + 1;
                queens.pop();
            }
        }
        else{
            if(queens.top == -1) break;
            col = queens.column[queens.top] + 1;
            queens.pop();
        }
    }
    cout << "Total solutions: " << solutions << "\n";
}
