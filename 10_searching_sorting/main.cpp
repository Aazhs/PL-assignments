#include <iostream>
#include <cstring>
using namespace std;

// Student database (15 records in a plain array) with different
// sorting and searching algorithms. Each sort works on a different field.
// Note: every sort rearranges the same global array 's'.
const int N = 15;

struct Student {
    int rollNo;
    char name[30];
    float sgpa;
    char dept[20];
};

Student s[N] = {
    {5, "Sneha Kulkarni", 8.40, "Computer"},
    {12, "Amit Patil", 7.85, "IT"},
    {1, "Rahul Sharma", 9.20, "Computer"},
    {8, "Pooja Deshmukh", 8.50, "Electronics"},
    {3, "Kiran Joshi", 7.10, "Mechanical"},
    {15, "Neha Gupta", 9.65, "Computer"},
    {7, "Aditya Pawar", 8.00, "Civil"},
    {10, "Ankita More", 9.20, "IT"},
    {2, "Vikram Singh", 6.90, "Computer"},
    {14, "Amit Patil", 8.75, "Computer"},
    {6, "Shreya Iyer", 8.50, "IT"},
    {11, "Rohan Mehta", 7.40, "Electronics"},
    {4, "Divya Nair", 9.00, "Computer"},
    {13, "Omkar Jadhav", 8.25, "Mechanical"},
    {9, "Tanvi Kale", 8.50, "Computer"}
};

// Print the first 'count' students as a table
void print(int count) {
    cout << "Roll\tName\t\t\tSGPA\tDepartment\n";
    for (int i = 0; i < count; i++) {
        cout << s[i].rollNo << "\t" << s[i].name << "\t\t" << s[i].sgpa << "\t" << s[i].dept << "\n";
    }
}

// Swap two whole student records (used by the sorts)
void swapStudents(int a, int b) {
    Student temp = s[a];
    s[a] = s[b];
    s[b] = temp;
}

// Bubble sort by roll number
// Compare neighbours and swap if they are in the wrong order. Each pass
// "bubbles" the largest remaining roll number to the end. O(n^2)
void bubbleSort() {
    for (int i = 0; i < N - 1; i++) {
        // After pass i, the last i records are already in place
        for (int j = 0; j < N - 1 - i; j++) {
            if (s[j].rollNo > s[j + 1].rollNo) {
                swapStudents(j, j + 1);
            }
        }
    }
}

// Insertion sort by name
// Like sorting playing cards in hand: the left part is already sorted;
// take the next record (key) and slide it left into its correct place. O(n^2)
void insertionSort() {
    for (int i = 1; i < N; i++) {
        Student key = s[i];
        int j = i - 1;
        // Shift names that come after key one step right (strcmp > 0 means s[j] comes after key)
        while (j >= 0 && strcmp(s[j].name, key.name) > 0) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;  // drop key into the gap that was made
    }
}

// Selection sort by SGPA (lowest first)
// Each pass "selects" the smallest remaining value and puts it in front. O(n^2)
void selectionSort() {
    for (int i = 0; i < N - 1; i++) {
        // Find the lowest SGPA in the unsorted part and swap it into position i
        int min = i;
        for (int j = i + 1; j < N; j++) {
            if (s[j].sgpa < s[min].sgpa) {
                min = j;
            }
        }
        swapStudents(i, min);
    }
}

// Quick sort by SGPA (highest first)
// Divide and conquer: pick a pivot, put bigger SGPAs on its left and smaller
// on its right, then sort both sides the same way (recursion). Avg O(n log n)
void quickSort(int low, int high) {
    // 0 or 1 element: already sorted
    if (low >= high) {
        return;
    }

    // Last element is the pivot; move every SGPA >= pivot to the left side
    float pivot = s[high].sgpa;
    int i = low - 1;  // end of the "SGPA >= pivot" side
    for (int j = low; j < high; j++) {
        if (s[j].sgpa >= pivot) {
            i++;
            swapStudents(i, j);
        }
    }
    // Put the pivot just after the left side; that is its final position
    swapStudents(i + 1, high);

    // Pivot is at i + 1, so sort the part before it and the part after it
    quickSort(low, i);
    quickSort(i + 2, high);
}

// Linear search: print every student with this SGPA
// Check every record one by one; works on unsorted data. O(n)
void linearSearch(float key) {
    int found = 0;
    for (int i = 0; i < N; i++) {
        if (s[i].sgpa == key) {
            cout << s[i].rollNo << "\t" << s[i].name << "\t\t" << s[i].sgpa << "\t" << s[i].dept << "\n";
            found++;
        }
    }
    if (found == 0) {
        cout << "No student has SGPA " << key << "\n";
    }
}

// Binary search by name (array must be sorted by name)
// Look at the middle name; throw away the half that can't contain key,
// and repeat on the other half. O(log n). Returns index, or -1 if not found.
int binarySearch(char key[]) {
    int low = 0, high = N - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(s[mid].name, key);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            // Middle name comes before key, so search the right half
            low = mid + 1;
        } else {
            // Middle name comes after key, so search the left half
            high = mid - 1;
        }
    }
    return -1;
}

// Fibonacci search by roll number (array must be sorted by roll number)
// Like binary search, but the array is split using Fibonacci numbers
// (0, 1, 1, 2, 3, 5, 8, 13, ...) instead of exactly in half. O(log n)
// a, b, fib are always three consecutive Fibonacci numbers (a + b = fib).
int fibonacciSearch(int key) {
    // Find the smallest Fibonacci number fib >= N; a and b are the two before it
    int a = 0, b = 1, fib = 1;
    while (fib < N) {
        a = b;
        b = fib;
        fib = a + b;
    }

    // offset = index of the last element known to be smaller than key
    int offset = -1;
    while (fib > 1) {
        // Index to check; clamp it so it doesn't go past the array end
        int i = offset + a;
        if (i > N - 1) {
            i = N - 1;
        }

        if (s[i].rollNo < key) {
            // Key is bigger: skip the part up to i, step the numbers down once
            fib = b;
            b = a;
            a = fib - b;
            offset = i;
        } else if (s[i].rollNo > key) {
            // Key is smaller: keep only the part before i, step the numbers down twice
            fib = a;
            b = b - a;
            a = fib - b;
        } else {
            return i;
        }
    }

    // One element may still be left unchecked
    if (b == 1 && offset + 1 < N && s[offset + 1].rollNo == key) {
        return offset + 1;
    }
    return -1;
}

int main() {
    int choice;

    do {
        cout << "\n1. Roll call list (Bubble sort)\n";
        cout << "2. Alphabetical list (Insertion sort)\n";
        cout << "3. SGPA list, lowest first (Selection sort)\n";
        cout << "4. First ten toppers (Quick sort)\n";
        cout << "5. Search by SGPA (Linear search)\n";
        cout << "6. Search by name (Binary search)\n";
        cout << "7. Check Computer department (Fibonacci search)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bubbleSort();
                print(N);
                break;
            case 2:
                insertionSort();
                print(N);
                break;
            case 3:
                selectionSort();
                print(N);
                break;
            case 4:
                // Sorted highest SGPA first, so the first 10 rows are the toppers
                quickSort(0, N - 1);
                print(10);
                break;
            case 5: {
                float key;
                cout << "Enter SGPA: ";
                cin >> key;
                linearSearch(key);
                break;
            }
            case 6: {
                char key[30];
                // Drop the newline left by cin >> before reading a full line
                cin.ignore();
                cout << "Enter name: ";
                cin.getline(key, 30);
                insertionSort();  // binary search needs the array sorted by name
                int pos = binarySearch(key);
                if (pos == -1) {
                    cout << "Not found\n";
                } else {
                    cout << s[pos].rollNo << "\t" << s[pos].name << "\t\t" << s[pos].sgpa << "\t" << s[pos].dept << "\n";
                }
                break;
            }
            case 7: {
                int key;
                cout << "Enter roll number: ";
                cin >> key;
                bubbleSort();  // Fibonacci search needs the array sorted by roll number
                int pos = fibonacciSearch(key);
                if (pos == -1) {
                    cout << "Not found\n";
                } else if (strcmp(s[pos].dept, "Computer") == 0) {
                    cout << s[pos].name << " belongs to Computer department\n";
                } else {
                    cout << s[pos].name << " does not belong to Computer department\n";
                }
                break;
            }
            case 8:
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 8);

    return 0;
}
