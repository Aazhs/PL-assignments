/*
PRACTICE PROBLEM 7: TOWER OF HANOI USING RECURSION

PROBLEM:
Move n disks from rod A to rod C using spare rod B.
Move only one disk at a time, and never put a larger disk on a smaller disk.
The program prints each move in order.

EXAMPLE:
For 2 disks: disk 1 A -> B, disk 2 A -> C, disk 1 B -> C.

HOW TO SOLVE:
1. If n == 0, there is nothing to move: return immediately.
2. Move the top n-1 disks from source to auxiliary using destination as spare.
3. Move disk n (the largest in this group) from source to destination.
4. Move the n-1 disks from auxiliary to destination using source as spare.
Each smaller task uses the same function: this is recursion.

VARIABLES / IMPORTANT POINTS:
source = current starting rod; auxiliary = spare rod; destination = target.
The rods change roles in recursive calls; their letters stay A, B and C.
The base case stops the recursion. A valid solution prints 2^n - 1 moves.
Input is limited to 1 through 15 disks so the output stays manageable.
*/

#include <iostream>
using namespace std;

// Solve a smaller transfer on each side of the largest-disk move; n == 0 ends recursion.
void hanoi(int n, char source, char auxiliary, char destination)
{
    if (n == 0) return; // Base case: no disks to move.

    // Step 1: move the smaller n-1 disks out of the way.
    // For this smaller call, the old spare rod becomes the target; the old target is spare.
    hanoi(n - 1, source, destination, auxiliary);

    // Step 2: move the largest disk directly to the destination.
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;

    // Step 3: put the smaller disks on top of the largest disk.
    // The smaller stack now starts on auxiliary; source is available as its spare rod.
    hanoi(n - 1, auxiliary, source, destination);
}

// Read a small positive disk count and start the transfer with A as source and C as target.
int main()
{
    int n;
    cout << "Enter number of disks (1 to 15): ";
    if (!(cin >> n) || n < 1 || n > 15) return 0;
    // A is the starting rod, B is spare, and C is the target rod.
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
