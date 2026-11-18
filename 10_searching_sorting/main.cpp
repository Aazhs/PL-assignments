#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Student database (15 records in a plain array) with different
// sorting and searching algorithms. Each sort works on a different field.
// Note: every sort rearranges the same global array 's'.
const int N = 15;

class Student {
public:
    int rollNo;
    string name;
    float sgpa;
    string dept;

    Student() {}

    Student(int rollNo, string name, float sgpa, string dept) {
        this->rollNo = rollNo;
        this->name = name;
        this->sgpa = sgpa;
        this->dept = dept;
    }
};

Student students[N] = {
    Student(5, "Sneha Kulkarni", 8.40, "Computer"),
    Student(12, "Amit Patil", 7.85, "IT"),
    Student(1, "Rahul Sharma", 9.20, "Computer"),
    Student(8, "Pooja Deshmukh", 8.50, "Electronics"),
    Student(3, "Kiran Joshi", 7.10, "Mechanical"),
    Student(15, "Neha Gupta", 9.65, "Computer"),
    Student(7, "Aditya Pawar", 8.00, "Civil"),
    Student(10, "Ankita More", 9.20, "IT"),
    Student(2, "Vikram Singh", 6.90, "Computer"),
    Student(14, "Amit Patil", 8.75, "Computer"),
    Student(6, "Shreya Iyer", 8.50, "IT"),
    Student(11, "Rohan Mehta", 7.40, "Electronics"),
    Student(4, "Divya Nair", 9.00, "Computer"),
    Student(13, "Omkar Jadhav", 8.25, "Mechanical"),
    Student(9, "Tanvi Kale", 8.50, "Computer")
};

void printStudents(int count) {
    cout << "\nRoll\tName\t\t\tSGPA\tDepartment\n";

    for (int i = 0; i < count; i++) {
        cout << students[i].rollNo << "\t"
             << students[i].name << "\t\t"
             << students[i].sgpa << "\t"
             << students[i].dept << "\n";
    }
}

// Swap two whole student records (used by the sorts)
void swapStudents(int a, int b) {
    Student temp = students[a];
    students[a] = students[b];
    students[b] = temp;
}

// Bubble sort by roll number
// Type: comparison sort using repeated adjacent exchanges (exchange sort).
// Compare neighbours and swap if they are in the wrong order. Each pass
// "bubbles" the largest remaining roll number to the end. O(n^2)
void bubbleSort() {
    // After i passes, the last i records are already in their final positions.
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swapStudents(j, j + 1);
            }
        }
    }
}

// Insertion sort by name
// Type: comparison sort; decrease and conquer (sort one fewer item, then insert).
// Like sorting playing cards in hand: the left part is already sorted;
// take the next record (key) and slide it left into its correct place. O(n^2)
void insertionSort() {
    for (int i = 1; i < N; i++) {
        // Save this record before shifting larger names one position right.
        Student key = students[i];
        int j = i - 1;

        while (j >= 0 && students[j].name > key.name) {
            students[j + 1] = students[j];
            j--;
        }

        // j is just before the gap where the saved name belongs.
        students[j + 1] = key;
    }
}

// Selection sort by SGPA, lowest first
// Type: comparison sort using repeated minimum selection (selection sort).
// Find the smallest SGPA in the unsorted suffix and put it at position i.
// The sorted prefix grows by one record each pass. O(n^2) comparisons.
void selectionSort() {
    for (int i = 0; i < N - 1; i++) {
        // Store the index of the smallest value seen, not the value itself.
        int minimum = i;

        for (int j = i + 1; j < N; j++) {
            if (students[j].sgpa < students[minimum].sgpa) {
                minimum = j;
            }
        }

        swapStudents(i, minimum);
    }
}

// Quick sort by SGPA, highest first
// Type: divide and conquer; partition, recursively sort both sides, no merge needed.
// Partition around a pivot, then recursively partition the two remaining sides.
// Average time O(n log n); worst case O(n^2) with unbalanced partitions.
void quickSort(int low, int high) {
    // 0 or 1 element: already sorted
    if (low >= high) {
        return;
    }

    // Use the last SGPA as pivot; i marks the end of the >= pivot region.
    float pivot = students[high].sgpa;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (students[j].sgpa >= pivot) {
            i++;
            swapStudents(i, j);
        }
    }

    // Put the pivot between the higher/equal and lower SGPA regions.
    swapStudents(i + 1, high);

    int pivotPosition = i + 1;

    quickSort(low, pivotPosition - 1);
    quickSort(pivotPosition + 1, high);
}

// Linear search by SGPA
// Type: brute force / sequential search; inspect records one at a time.
// Check every record; no sorting is needed. Continue after a match so all
// students with the requested SGPA are printed. O(n) time.
void linearSearch(float key) {
    int found = 0;

    for (int i = 0; i < N; i++) {
        if (students[i].sgpa == key) {
            cout << students[i].rollNo << "\t"
                 << students[i].name << "\t\t"
                 << students[i].sgpa << "\t"
                 << students[i].dept << "\n";

            found++;
        }
    }

    if (found == 0) {
        cout << "No student has SGPA " << key << "\n";
    }
}

// Binary search by name
// Type: decrease and conquer by a constant factor; keep only one half each step.
// Often grouped with divide and conquer, but only one subproblem is searched.
// Requires names in ascending order. Compare the middle name and discard
// the half that cannot contain the key. Each step halves the range: O(log n).
int binarySearch(string key) {
    int low = 0;
    int high = N - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (students[middle].name == key) {
            return middle;
        }
        else if (students[middle].name < key) {
            // Key comes after the middle name, so keep only the right half.
            low = middle + 1;
        }
        else {
            // Key comes before the middle name, so keep only the left half.
            high = middle - 1;
        }
    }

    return -1;
}

// Fibonacci search by roll number
// Type: decrease and conquer; reduce the search range using Fibonacci sizes.
// Requires ascending roll numbers. Use Fibonacci sizes to split the remaining
// range instead of its midpoint; shrink those sizes after each comparison.
// Time O(log n), extra space O(1).
int fibonacciSearch(int key) {
    int a = 0;
    int b = 1;
    int fib = 1;

    // Build consecutive Fibonacci numbers a, b, fib until fib covers the array.
    while (fib < N) {
        a = b;
        b = fib;
        fib = a + b;
    }

    // Everything at or before offset has been eliminated from consideration.
    int offset = -1;

    while (fib > 1) {
        int index = offset + a;

        // The Fibonacci range can exceed N; keep the probe inside the array.
        if (index >= N) {
            index = N - 1;
        }

        if (students[index].rollNo < key) {
            // Discard through index and move to the next smaller Fibonacci range.
            fib = b;
            b = a;
            a = fib - b;
            offset = index;
        }
        else if (students[index].rollNo > key) {
            // Keep the left range, shrinking by two Fibonacci levels.
            fib = a;
            b = b - a;
            a = fib - b;
        }
        else {
            return index;
        }
    }

    // One possible element may remain after the main probing loop.
    if (b == 1 &&
        offset + 1 < N &&
        students[offset + 1].rollNo == key) {
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
            printStudents(N);
            break;

        case 2:
            insertionSort();
            printStudents(N);
            break;

        case 3:
            selectionSort();
            printStudents(N);
            break;

        case 4:
            // Sorted highest SGPA first, so the first 10 rows are the toppers
            quickSort(0, N - 1);
            printStudents(10);
            break;

        case 5: {
            float key;

            cout << "Enter SGPA: ";
            cin >> key;

            linearSearch(key);
            break;
        }

        case 6: {
            string key;

            // Drop the newline left by cin >> before reading a full line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter name: ";
            getline(cin, key);

            insertionSort();  // binary search needs the array sorted by name

            int position = binarySearch(key);

            if (position == -1) {
                cout << "Not found\n";
            }
            else {
                cout << students[position].rollNo << "\t"
                     << students[position].name << "\t\t"
                     << students[position].sgpa << "\t"
                     << students[position].dept << "\n";
            }

            break;
        }

        case 7: {
            int key;

            cout << "Enter roll number: ";
            cin >> key;

            bubbleSort();  // Fibonacci search needs the array sorted by roll number

            int position = fibonacciSearch(key);

            if (position == -1) {
                cout << "Not found\n";
            }
            else if (students[position].dept == "Computer") {
                cout << students[position].name
                     << " belongs to Computer department\n";
            }
            else {
                cout << students[position].name
                     << " does not belong to Computer department\n";
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
