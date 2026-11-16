/*
PRACTICE PROBLEM 12: STUDENT PERCENTAGES USING MERGE SORT

PROBLEM:
Store student percentages in a floating-point array and sort them in
ascending order using Merge Sort, rather than a built-in sort function.

EXAMPLE:
Input: 90.5 60 75.25 -> output: 60 75.25 90.5.

HOW TO SOLVE:
1. Read n percentages into an array.
2. mergeSort() divides the current range into left and right halves.
3. Recursively sort each half until ranges have at most one element.
4. merge() compares the two sorted halves and takes the smaller next value.
5. Copy remaining values from either unfinished half, then copy temp back.
6. Display the final sorted array.

VARIABLES / IMPORTANT POINTS:
left/right are inclusive boundaries; mid divides them.
i scans the left half, j the right half, and k writes into temp.
Using <= takes the left value first when values tie, preserving their order.
Input allows 0 to 100 students and percentages between 0 and 100.
*/

#include <iostream>
using namespace std;

// Combine the two already sorted inclusive ranges [left..mid] and [mid+1..right].
void merge(float arr[], int left, int mid, int right)
{
    float temp[100];
    // Each half has its own read cursor; k writes into the same range of the temporary array.
    int i = left, j = mid + 1, k = left;

    // Both halves are sorted. Take the smaller front value each time.
    while (i <= mid && j <= right)
    {
        // Choosing the left item on equality makes the merge stable for duplicate percentages.
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // One half may finish first. Copy the remaining values from the other.
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    // Copy back only this merged range; other portions of arr are left untouched.
    for (int index = left; index <= right; index++) arr[index] = temp[index];
}

// Divide a range into smaller ranges, sort them recursively, then merge their answers.
void mergeSort(float arr[], int left, int right)
{
    if (left >= right) return; // One element, or no elements, is already sorted.
    // Both halves become smaller, so recursion eventually reaches a range of one element.
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid); // Sort the left half.
    mergeSort(arr, mid + 1, right); // Sort the right half.
    merge(arr, left, mid, right); // Join the sorted halves.
}

// Read valid percentages, sort indices 0 through n-1, and display the ascending values.
int main()
{
    float percentage[100];
    int n;
    cout << "Enter student count (0 to 100): ";
    if (!(cin >> n) || n < 0 || n > 100) return 0;
    cout << "Enter percentages (0 to 100): ";
    for (int i = 0; i < n; i++)
        if (!(cin >> percentage[i]) || percentage[i] < 0 || percentage[i] > 100) return 0;

    mergeSort(percentage, 0, n - 1);
    cout << "Percentages in ascending order: ";
    for (int i = 0; i < n; i++) cout << percentage[i] << " ";
    cout << endl;
    return 0;
}
