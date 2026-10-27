#include <iostream>
#include <cstring>
using namespace std;

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

void print(int count) {
    cout << "Roll\tName\t\t\tSGPA\tDepartment\n";
    for (int i = 0; i < count; i++) {
        cout << s[i].rollNo << "\t" << s[i].name << "\t\t" << s[i].sgpa << "\t" << s[i].dept << "\n";
    }
}

void swapStudents(int a, int b) {
    Student temp = s[a];
    s[a] = s[b];
    s[b] = temp;
}

// Bubble sort by roll number
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
void insertionSort() {
    for (int i = 1; i < N; i++) {
        Student key = s[i];
        int j = i - 1;
        // Shift names that come after key one step right (strcmp > 0 means s[j] comes after key)
        while (j >= 0 && strcmp(s[j].name, key.name) > 0) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

// Selection sort by SGPA (lowest first)
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
void quickSort(int low, int high) {
    if (low >= high) {
        return;
    }

    // Last element is the pivot; move every SGPA >= pivot to the left side
    float pivot = s[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (s[j].sgpa >= pivot) {
            i++;
            swapStudents(i, j);
        }
    }
    // Put the pivot just after the left side; that is its final position
    swapStudents(i + 1, high);

    quickSort(low, i);
    quickSort(i + 2, high);
}

// Linear search: print every student with this SGPA
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
            high = mid - 1;
        }
    }
    return -1;
}

// Fibonacci search by roll number (array must be sorted by roll number)
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
                insertionSort();
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
                bubbleSort();
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
