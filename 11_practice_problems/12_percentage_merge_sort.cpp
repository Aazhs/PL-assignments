#include <iostream>
using namespace std;

void merge(float arr[], int left, int mid, int right)
{
    float temp[100];
    int i = left, j = mid + 1, k = left;

    // Both halves are sorted. Take the smaller front value each time.
    while (i <= mid && j <= right)
    {
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
    for (int index = left; index <= right; index++) arr[index] = temp[index];
}

void mergeSort(float arr[], int left, int right)
{
    if (left >= right) return; // One element, or no elements, is already sorted.
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid); // Sort the left half.
    mergeSort(arr, mid + 1, right); // Sort the right half.
    merge(arr, left, mid, right); // Join the sorted halves.
}

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
