#include <iostream>
using namespace std;

// How this program works:
// For 3 disks: move 2 aside, move disk 3 to C, then move 2 onto disk 3.
// The same rule works for every smaller group of disks.
// source, auxiliary and destination change roles in each recursive call.

// Move n-1 disks aside, move the largest disk, then move n-1 onto it.
void hanoi(int n, char source, char auxiliary, char destination){
    if(n == 0) return; // Base case: no disks left to move.
    hanoi(n - 1, source, destination, auxiliary);
    cout << "Move disk " << n << " from " << source << " to " << destination << "\n";
    hanoi(n - 1, auxiliary, source, destination);
}
// Program starts here: read inputs, then perform the requested operations.
int main(){
    int n;
    cout << "Enter number of disks (1 to 15): ";
    if(!(cin >> n) || n < 1 || n > 15){ cout << "Invalid disk count.\n"; return 0; }
    hanoi(n, 'A', 'B', 'C');
    cout << "Total moves: " << (1LL << n) - 1 << "\n";
}
