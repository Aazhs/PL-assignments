#include <iostream>
using namespace std;

void hanoi(int n, char source, char auxiliary, char destination)
{
    if (n == 0) return; // Base case: no disks to move.

    // Step 1: move the smaller n-1 disks out of the way.
    hanoi(n - 1, source, destination, auxiliary);

    // Step 2: move the largest disk directly to the destination.
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;

    // Step 3: put the smaller disks on top of the largest disk.
    hanoi(n - 1, auxiliary, source, destination);
}

int main()
{
    int n;
    cout << "Enter number of disks (1 to 15): ";
    if (!(cin >> n) || n < 1 || n > 15) return 0;
    // A is the starting rod, B is spare, and C is the target rod.
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
