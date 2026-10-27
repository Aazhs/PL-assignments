#include <iostream>
#include <cstring>
using namespace std;

// Student record: roll number, name, SGPA and department
struct Student {
    int rollNo;
    char name[30];
    float sgpa;
    char dept[20];
};

class Algorithm {
private:
    static const int N = 15;   // Number of student records

    Student students[N];       // Original database (array defined inside the class)
    Student work[N];           // Working copy used by each operation

    // Fill the original database with 15 records
    void setRecord(int i, int roll, const char nm[], float g, const char d[]) {
        students[i].rollNo = roll;
        strcpy(students[i].name, nm);
        students[i].sgpa = g;
        strcpy(students[i].dept, d);
    }

    void loadRecords() {
        setRecord(0, 5, "Sneha Kulkarni", 8.40, "Computer");
        setRecord(1, 12, "Amit Patil", 7.85, "IT");
        setRecord(2, 1, "Rahul Sharma", 9.20, "Computer");
        setRecord(3, 8, "Pooja Deshmukh", 8.50, "Electronics");
        setRecord(4, 3, "Kiran Joshi", 7.10, "Mechanical");
        setRecord(5, 15, "Neha Gupta", 9.65, "Computer");
        setRecord(6, 7, "Aditya Pawar", 8.00, "Civil");
        setRecord(7, 10, "Ankita More", 9.20, "IT");
        setRecord(8, 2, "Vikram Singh", 6.90, "Computer");
        setRecord(9, 14, "Amit Patil", 8.75, "Computer");
        setRecord(10, 6, "Shreya Iyer", 8.50, "IT");
        setRecord(11, 11, "Rohan Mehta", 7.40, "Electronics");
        setRecord(12, 4, "Divya Nair", 9.00, "Computer");
        setRecord(13, 13, "Omkar Jadhav", 8.25, "Mechanical");
        setRecord(14, 9, "Tanvi Kale", 8.50, "Computer");
    }

    // Copy the original database into the working array
    void loadCopy() {
        for (int i = 0; i < N; i++) {
            work[i] = students[i];
        }
    }

    // Print the table heading
    void printHeader() {
        cout << "Roll\tName\t\t\tSGPA\tDepartment" << endl;
        cout << "-------------------------------------------------------" << endl;
    }

    // Print one student record
    void printStudent(Student s) {
        cout << s.rollNo << "\t" << s.name << "\t\t" << s.sgpa << "\t" << s.dept << endl;
    }

    // Print all records in the working array
    void printWork() {
        printHeader();
        for (int i = 0; i < N; i++) {
            printStudent(work[i]);
        }
    }

    // 1. Bubble sort: ascending by roll number
    void bubbleSortByRoll() {
        for (int i = 0; i < N - 1; i++) {
            // After pass i, the last i records are already in place, so skip them
            for (int j = 0; j < N - 1 - i; j++) {
                if (work[j].rollNo > work[j + 1].rollNo) {
                    Student temp = work[j];
                    work[j] = work[j + 1];
                    work[j + 1] = temp;
                }
            }
        }
    }

    // 2. Insertion sort: alphabetical by name
    void insertionSortByName() {
        for (int i = 1; i < N; i++) {
            // Take out work[i] and shift names that come after it one step right until its spot is found
            // (strcmp > 0 means work[j].name comes after key alphabetically)
            Student key = work[i];
            int j = i - 1;
            while (j >= 0 && strcmp(work[j].name, key.name) > 0) {
                work[j + 1] = work[j];
                j--;
            }
            work[j + 1] = key;
        }
    }

    // 3. Selection sort: ascending by SGPA (lowest first)
    void selectionSortBySgpa() {
        for (int i = 0; i < N - 1; i++) {
            // Find the lowest SGPA in the unsorted part and swap it into position i
            int minIndex = i;
            for (int j = i + 1; j < N; j++) {
                if (work[j].sgpa < work[minIndex].sgpa) {
                    minIndex = j;
                }
            }
            Student temp = work[i];
            work[i] = work[minIndex];
            work[minIndex] = temp;
        }
    }

    // 4. Quick sort helper: partition so that higher SGPA comes first
    int partitionBySgpa(int low, int high) {
        // The last record is the pivot. Records with SGPA >= pivot are moved to the left part;
        // i is the end of that left part.
        float pivot = work[high].sgpa;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (work[j].sgpa >= pivot) {
                i++;
                Student temp = work[i];
                work[i] = work[j];
                work[j] = temp;
            }
        }
        // Put the pivot right after the left part; this is its final sorted position
        Student temp = work[i + 1];
        work[i + 1] = work[high];
        work[high] = temp;
        return i + 1;
    }

    // 4. Quick sort: descending by SGPA (toppers first)
    void quickSortBySgpa(int low, int high) {
        if (low < high) {
            // Pivot is now in place; sort the parts on both sides of it
            int p = partitionBySgpa(low, high);
            quickSortBySgpa(low, p - 1);
            quickSortBySgpa(p + 1, high);
        }
    }

    // 6. Fibonacci search (iterative) on work[], sorted by roll number.
    // Returns the index of the record, or -1 if not found.
    int fibonacciSearch(int key) {
        int fibMm2 = 0;              // (m-2)th Fibonacci number
        int fibMm1 = 1;              // (m-1)th Fibonacci number
        int fibM = fibMm2 + fibMm1;  // m-th Fibonacci number, first one >= N

        // Find the smallest Fibonacci number that is >= N
        while (fibM < N) {
            fibMm2 = fibMm1;
            fibMm1 = fibM;
            fibM = fibMm2 + fibMm1;
        }

        // offset = index of the last element known to be smaller than key
        int offset = -1;
        while (fibM > 1) {
            // Check the element fibMm2 steps after offset (but not past the last index)
            int i = offset + fibMm2;
            if (i > N - 1) {
                i = N - 1;
            }

            // Key is bigger: drop the part before i, move the Fibonacci numbers one step down
            if (work[i].rollNo < key) {
                fibM = fibMm1;
                fibMm1 = fibMm2;
                fibMm2 = fibM - fibMm1;
                offset = i;
            } else if (work[i].rollNo > key) {
                // Key is smaller: drop the part after i, move the Fibonacci numbers two steps down
                fibM = fibMm2;
                fibMm1 = fibMm1 - fibMm2;
                fibMm2 = fibM - fibMm1;
            } else {
                return i;
            }
        }

        // One element may still be unchecked; compare it
        if (fibMm1 == 1 && offset + 1 < N && work[offset + 1].rollNo == key) {
            return offset + 1;
        }
        return -1;
    }

public:
    Algorithm() {
        loadRecords();
    }

    // Option 1: Roll call list (Bubble sort)
    void rollCallList() {
        loadCopy();
        bubbleSortByRoll();
        cout << "\n--- Roll Call List (Bubble Sort) ---\n";
        printWork();
    }

    // Option 2: Alphabetical list (Insertion sort)
    void alphabeticalList() {
        loadCopy();
        insertionSortByName();
        cout << "\n--- Alphabetical List (Insertion Sort) ---\n";
        printWork();
    }

    // Option 3: SGPA in ascending order (Selection sort)
    void selectionSortList() {
        loadCopy();
        selectionSortBySgpa();
        cout << "\n--- SGPA List, Lowest First (Selection Sort) ---\n";
        printWork();
    }

    // Option 4: First ten toppers (Quick sort)
    void firstTenToppers() {
        loadCopy();
        quickSortBySgpa(0, N - 1);
        cout << "\n--- First Ten Toppers (Quick Sort) ---\n";
        printHeader();
        for (int i = 0; i < 10 && i < N; i++) {
            cout << (i + 1) << ". ";
            printStudent(work[i]);
        }
    }

    // Option 5: Linear search, prints ALL students with this SGPA
    void searchBySgpa(float key) {
        cout << "\n--- Students with SGPA " << key << " (Linear Search) ---\n";
        int found = 0;
        for (int i = 0; i < N; i++) {
            // Exact float comparison works because the key and the stored SGPA are both float
            if (students[i].sgpa == key) {
                if (found == 0) {
                    printHeader();
                }
                printStudent(students[i]);
                found++;
            }
        }
        if (found == 0) {
            cout << "No student has SGPA " << key << endl;
        } else {
            cout << "Students with SGPA " << key << ": " << found << endl;
        }
    }

    // Option 6: Binary search (iterative) by name.
    // The list is sorted alphabetically first; all records with the name are printed.
    void searchByName(char key[]) {
        loadCopy();
        insertionSortByName();
        cout << "\n--- Search Result for \"" << key << "\" (Binary Search) ---\n";

        int low = 0;
        int high = N - 1;
        int pos = -1;

        // Binary search on the alphabetically sorted list
        while (low <= high) {
            int mid = (low + high) / 2;
            int cmp = strcmp(work[mid].name, key);
            if (cmp == 0) {
                pos = mid;
                break;
            } else if (cmp < 0) {
                // Middle name comes before key alphabetically, so search the right half
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (pos == -1) {
            cout << "Student named " << key << " not found." << endl;
            return;
        }

        // Records with the same name sit next to each other after sorting,
        // so expand left and right from pos to find all of them
        int first = pos;
        while (first > 0 && strcmp(work[first - 1].name, key) == 0) {
            first--;
        }
        int last = pos;
        while (last < N - 1 && strcmp(work[last + 1].name, key) == 0) {
            last++;
        }

        printHeader();
        for (int i = first; i <= last; i++) {
            printStudent(work[i]);
        }
        cout << "Total records found: " << (last - first + 1) << endl;
    }

    // Option 7: Fibonacci search by roll number, then check the department
    void checkComputerDept(int rollKey) {
        loadCopy();
        bubbleSortByRoll();
        cout << "\n--- Computer Department Check (Fibonacci Search) ---\n";

        int pos = fibonacciSearch(rollKey);
        if (pos == -1) {
            cout << "Roll No " << rollKey << " not found.\n";
        } else if (strcmp(work[pos].dept, "Computer") == 0) {
            cout << work[pos].name << " (Roll No " << rollKey
                 << ") BELONGS to the Computer department.\n";
        } else {
            cout << work[pos].name << " (Roll No " << rollKey
                 << ") does NOT belong to the Computer department.\n";
        }
    }
};

int main() {
    Algorithm db;   // Object holding the array and all the operations

    int choice;
    float sgpaKey;
    char nameKey[30];
    int rollKey;

    do {
        cout << "\n===== STUDENT DATABASE MENU =====\n";
        cout << "1. Roll call list (Bubble sort by roll no)\n";
        cout << "2. Alphabetical list (Insertion sort by name)\n";
        cout << "3. SGPA list, lowest first (Selection sort)\n";
        cout << "4. First ten toppers (Quick sort by SGPA)\n";
        cout << "5. Search by SGPA (Linear search)\n";
        cout << "6. Search by name (Binary search)\n";
        cout << "7. Check Computer department (Fibonacci search)\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                db.rollCallList();
                break;
            case 2:
                db.alphabeticalList();
                break;
            case 3:
                db.selectionSortList();
                break;
            case 4:
                db.firstTenToppers();
                break;
            case 5:
                cout << "Enter SGPA to search: ";
                cin >> sgpaKey;
                db.searchBySgpa(sgpaKey);
                break;
            case 6:
                // Drop the newline left by cin >> before reading a full line
                cin.ignore(10000, '\n');
                cout << "Enter name to search: ";
                cin.getline(nameKey, 30);
                db.searchByName(nameKey);
                break;
            case 7:
                cout << "Enter roll number to check: ";
                cin >> rollKey;
                db.checkComputerDept(rollKey);
                break;
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
