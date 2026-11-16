#include <iostream>
using namespace std;

// How this program works:
// Divide the array into halves until each part has at most one element.
// Merge sorted halves by repeatedly taking the smaller front value.
// Example: [70 90] and [60 80] merge into [60 70 80 90].

// Merge two sorted halves using a temporary array, then copy back.
void merge(float arr[], int left, int mid, int right){
    float temp[100];
    int i = left, j = mid + 1, k = left;
    while(i <= mid && j <= right){
        if(arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    // One half may still contain values; copy those remaining values.
    while(i <= mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    // Replace this portion of the original array with the sorted values.
    for(int index = left; index <= right; index++) arr[index] = temp[index];
}
void mergeSort(float arr[], int left, int right){
    if(left >= right) return; // Zero or one element is already sorted.
    // Split into [left..mid] and [mid+1..right].
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
// Program starts here: read inputs, then perform the requested operations.
int main(){
    float percentage[100]; int n;
    cout << "Enter student count (0 to 100): ";
    if(!(cin >> n) || n < 0 || n > 100) return 0;
    cout << "Enter percentages (0 to 100): ";
    for(int i = 0; i < n; i++){
        if(!(cin >> percentage[i]) || percentage[i] < 0 || percentage[i] > 100) return 0;
    }
    mergeSort(percentage, 0, n - 1);
    cout << "Percentages in ascending order: ";
    for(int i = 0; i < n; i++) cout << percentage[i] << " ";
    cout << "\n";
}
