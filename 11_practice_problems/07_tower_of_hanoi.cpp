#include <iostream>
using namespace std;

// Move n-1 disks aside, move the largest disk, then move n-1 onto it.
void hanoi(int n, char source, char auxiliary, char destination){
    if(n == 0) return; // Base case: no disks left to move.
    hanoi(n - 1, source, destination, auxiliary);
    cout << "Move disk " << n << " from " << source << " to " << destination << "\n";
    hanoi(n - 1, auxiliary, source, destination);
}
int main(){
    int n;
    cout << "Enter number of disks (1 to 15): ";
    if(!(cin >> n) || n < 1 || n > 15){ cout << "Invalid disk count.\n"; return 0; }
    hanoi(n, 'A', 'B', 'C');
    cout << "Total moves: " << (1LL << n) - 1 << "\n";
}
