/*
QUESTION 14: MEDICAL STOCK USING LINEAR PROBING

Problem: Store medicine details using key % 9. If a slot is occupied,
try the next position until a free slot is found.

Simple idea: One HashTable class with three arrays. No Medicine class.
key[i], name[i], and quantity[i] describe the medicine at position i.
key[i] == -1 means empty, so medicine keys must be non-negative.

Steps:
1. Choose without replacement or with replacement (the question is unclear).
2. If a key exists, update its name and quantity.
3. Otherwise scan from key % 9 to find a free slot, wrapping with % 9.
4. Without replacement, use the free slot. With replacement, move a foreign
   home occupant there first, then put the new medicine in its own home.
5. Display the table and search for a medicine key.

Example: Insert keys 0, 9, 1. Without replacement they occupy slots 0, 1, 2.
With replacement, key 1 takes slot 1 and key 9 moves to slot 2.
Use one-word medicine names or underscores. Input uses plain cin statements.
*/
#include <iostream>
#include <string>
using namespace std;

class HashTable
{
public:
    int key[9], quantity[9];
    string name[9];

    HashTable()
    {
        for (int i = 0; i < 9; i++) key[i] = -1;
    }

    int search(int value)
    {
        // Same probing sequence for searching and inserting.
        int home = value % 9;
        for (int i = 0; i < 9; i++)
        {
            int p = (home + i) % 9;
            if (key[p] == -1) return -1;
            if (key[p] == value) return p;
        }
        return -1;
    }

    void insert(int value, string medicine, int stock, int mode)
    {
        int p = search(value);
        if (p == -1)
        {
            int home = value % 9;
            p = home;
            while (key[p] != -1)
            {
                p = (p + 1) % 9;
                if (p == home)
                {
                    cout << "Table full.\n";
                    return;
                }
            }

            // In mode 2 only, reclaim home if its occupant belongs elsewhere.
            if (mode == 2 && key[home] != -1 && key[home] % 9 != home)
            {
                key[p] = key[home];
                name[p] = name[home];
                quantity[p] = quantity[home];
                p = home;
            }
        }

        // p is either the existing key's slot or the new insertion position.
        key[p] = value;
        name[p] = medicine;
        quantity[p] = stock;
    }

    void display()
    {
        cout << "Index\tKey\tMedicine\tQuantity\n";
        for (int i = 0; i < 9; i++)
        {
            cout << i << "\t";
            if (key[i] == -1) cout << "EMPTY\n";
            else cout << key[i] << "\t" << name[i] << "\t" << quantity[i] << endl;
        }
    }
};

int main()
{
    HashTable h;
    int n, mode, value, stock;
    string medicine;
    cout << "1. Without replacement  2. With replacement\nEnter mode: ";
    cin >> mode;
    if (mode != 1 && mode != 2) return 0;
    cout << "Enter number of medicines (0 to 9): ";
    cin >> n;
    if (n < 0 || n > 9) return 0;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter key, name and quantity: ";
        cin >> value >> medicine >> stock;
        if (value < 0 || stock < 0) return 0;
        h.insert(value, medicine, stock, mode);
    }
    h.display();

    cout << "Enter key to search: ";
    cin >> value;
    if (value < 0) return 0;
    int p = h.search(value);
    if (p == -1) cout << "Medicine not found.\n";
    else cout << h.name[p] << "\tQuantity: " << h.quantity[p] << endl;
    return 0;
}
