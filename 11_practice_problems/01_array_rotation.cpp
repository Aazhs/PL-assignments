/*
PRACTICE PROBLEM 1: ARRAY ROTATION

PROBLEM:
Move the elements of an array k places to the left and to the right.
Values that move past one end must come back at the other end.
Print both answers using the same original array.

EXAMPLE:
Array = 1 2 3 4 5, k = 2
Left rotation  = 3 4 5 1 2
Right rotation = 4 5 1 2 3

HOW TO SOLVE:
1. Read n, the n elements, and a non-negative rotation count k.
2. Make two copies so left rotation does not change the right input.
3. Reduce k using k % n: rotating n times gives the original order.
4. For left rotation, read from (i + k) % n into temporary position i.
5. For right rotation, place element i at temporary position (i + k) % n.
6. Copy the temporary values back and display the two arrays.

VARIABLES / IMPORTANT POINTS:
n = number of elements; i = array index; k = number of positions.
temp holds the answer while the old array is still being read.
% n wraps an index around the end. n must be at least 1 to use it.
The arrays hold at most 100 elements. A zero k leaves the array unchanged.
*/

#include <iostream>
using namespace std;

// Build the left-rotated answer without overwriting values still needed from arr.
void leftRotate(int arr[], int n, int k)
{
    // n rotations give the original array, so only keep the remainder.
    // For n = 5 and k = 7, only 2 positions matter; five moves complete a circle.
    k = k % n;
    // A separate buffer prevents a moved value from destroying an unread value.
    int temp[100];

    // The element k places ahead becomes the element at position i.
    // % n wraps the index back to the start of the array.
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[(i + k) % n];
    }

    // Copy the rotated values back into the array.
    for (int i = 0; i < n; i++)
    {
        arr[i] = temp[i];
    }
}

// Move each old value to its new right-rotation position, then copy temp back.
void rightRotate(int arr[], int n, int k)
{
    k = k % n;
    int temp[100];

    // Move each element k positions to the right, wrapping at the end.
    for (int i = 0; i < n; i++)
    {
        temp[(i + k) % n] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = temp[i];
    }
}

// Print the first n elements in index order; the unused array slots are ignored.
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Read and validate input, copy the original array, and print both independent rotations.
int main()
{

    // Only indices 0 through n-1 hold input; the remaining capacity is unused.
    int n, k, arr[100], left[100], right[100];

    cout << "Enter size of array (1 to 100): ";
    cin >> n;

    if (n < 1 || n > 100) return 0;

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

    }

    cout << "Enter k (0 or more): ";
    cin >> k;

    if (k < 0) return 0;

    // Separate copies let us show both rotations of the original array.
    for (int i = 0; i < n; i++)
    {
        left[i] = arr[i];
        right[i] = arr[i];
    }

    leftRotate(left, n, k);
    rightRotate(right, n, k);

    cout << "Left Rotation: ";
    display(left, n);
    cout << "Right Rotation: ";
    display(right, n);
    return 0;
}
