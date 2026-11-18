#include <iostream>
using namespace std;

// Parts (a) and (c): probing without replacement.
class Hash {
    int table[11];
    int size;
    bool quadratic;

public:
    Hash(int n, bool useQuadratic = false) {
        size = n;
        quadratic = useQuadratic;
        for (int i = 0; i < size; i++)
            table[i] = -1;
    }

    void insert(int key) {
        if (key < 0) {
            cout << "Enter non-negative key\n";
            return;
        }

        int start = key % size;
        for (int i = 0; i < size; i++) {
            int index = (start + (quadratic ? i * i : i)) % size;
            if (table[index] == -1) {
                table[index] = key;
                cout << key << " inserted at index " << index << endl;
                return;
            }
        }
        // Quadratic probing may exhaust its positions before the table is full.
        cout << "No free position in probing sequence\n";
    }

    void display() {
        cout << "\nIndex\tKey\n";
        for (int i = 0; i < size; i++) {
            cout << i << "\t";
            if (table[i] == -1)
                cout << "Empty";
            else
                cout << table[i];
            cout << endl;
        }
    }
};

// Part (b): separate chaining using linked lists.
class Node {
public:
    int key;
    Node* next;
    Node(int value) {
        key = value;
        next = nullptr;
    }
};

class ChainHash {
    Node* table[20];

public:
    ChainHash() {
        for (int i = 0; i < 20; i++)
            table[i] = nullptr;
    }

    ~ChainHash() {
        for (int i = 0; i < 20; i++) {
            while (table[i] != nullptr) {
                Node* temp = table[i];
                table[i] = temp->next;
                delete temp;
            }
        }
    }

    void insert(int key) {
        if (key < 0 || key > 100) {
            cout << "Enter marks between 0 and 100\n";
            return;
        }
        int index = key % 20;
        Node* node = new Node(key);
        if (table[index] == nullptr)
            table[index] = node;
        else {
            Node* temp = table[index];
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = node;
        }
    }

    void display() {
        cout << "\nIndex\tKeys\n";
        for (int i = 0; i < 20; i++) {
            cout << i << "\t";
            Node* temp = table[i];
            if (temp == nullptr) cout << "Empty";
            while (temp != nullptr) {
                cout << temp->key;
                if (temp->next != nullptr) cout << " -> ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    Hash drinks(6);
    ChainHash marks;
    Hash mangoes(11, true);
    int students[20] = {33, 56, 78, 12, 10, 67, 89, 99, 100, 23,
                        45, 71, 39, 62, 59, 90, 91, 20, 75, 66};
    int fruits[11] = {25, 15, 10, 5, 11, 19, 16, 36, 42, 28, 32};
    for (int i = 0; i < 20; i++) marks.insert(students[i]);
    for (int i = 0; i < 11; i++) mangoes.insert(fruits[i]);

    int choice, key;
    do {
        cout << "\n----- HASHING MENU -----\n";
        cout << "1. Insert cold drink key (linear probing, mod 6)\n";
        cout << "2. Display cold drink table\n";
        cout << "3. Display student marks (chaining, mod 20)\n";
        cout << "4. Display mango table (quadratic probing, mod 11)\n";
        cout << "5. Exit\nEnter choice: ";
        if (!(cin >> choice)) return 0;
        switch (choice) {
        case 1:
            cout << "Enter key: ";
            if (!(cin >> key)) return 0;
            drinks.insert(key);
            break;
        case 2: drinks.display(); break;
        case 3: marks.display(); break;
        case 4: mangoes.display(); break;
        case 5: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice\n";
        }
    } while (choice != 5);
}
