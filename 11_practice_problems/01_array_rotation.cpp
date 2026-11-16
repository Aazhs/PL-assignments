#include <iostream>
using namespace std;

void leftRotate(int arr[], int n, int k)
{
    // n rotations give the original array, so only keep the remainder.
    k = k % n;
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

void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int n, k, arr[100], left[100], right[100];

    cout << "Enter size of array (1 to 100): ";
    if (!(cin >> n) || n < 1 || n > 100) return 0;

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
        if (!(cin >> arr[i])) return 0;

    cout << "Enter k (0 or more): ";
    if (!(cin >> k) || k < 0) return 0;

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
