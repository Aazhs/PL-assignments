#include <iostream>
#include <string>
using namespace std;

struct Medicine
{
    int key, quantity;
    string name;
};

int search(Medicine table[], bool occupied[], int key)
{
    int home = key % 9;
    for (int step = 0; step < 9; step++)
    {
        int index = (home + step) % 9;
        if (!occupied[index]) return -1; // An empty slot ends the search.
        if (table[index].key == key) return index;
    }
    return -1;
}

void insert(Medicine table[], bool occupied[], Medicine item, bool replacement)
{
    int existing = search(table, occupied, item.key);
    if (existing != -1)
    {
        table[existing] = item; // Same key: update the medicine's stock.
        return;
    }

    int home = item.key % 9;
    int empty = -1;
    for (int step = 0; step < 9; step++)
    {
        int index = (home + step) % 9;
        if (!occupied[index])
        {
            empty = index;
            break;
        }
    }
    if (empty == -1)
    {
        cout << "Hash table full.\n";
        return;
    }

    // With replacement: move a foreign occupant out of the new key's home.
    // Without replacement: simply use the first empty slot found above.
    if (replacement && occupied[home] && table[home].key % 9 != home)
    {
        table[empty] = table[home];
        table[home] = item;
    }
    else table[empty] = item;
    occupied[empty] = true;
}

void display(Medicine table[], bool occupied[])
{
    cout << "Index\tKey\tMedicine\tQuantity\n";
    for (int i = 0; i < 9; i++)
    {
        cout << i << "\t";
        if (!occupied[i]) cout << "EMPTY\n";
        else cout << table[i].key << "\t" << table[i].name << "\t" << table[i].quantity << endl;
    }
}

int main()
{
    Medicine table[9], item;
    bool occupied[9] = {}; // All slots start empty.
    int mode, n;
    // The PDF's wording is unclear, so either probing variant can be selected.
    cout << "1. Without replacement  2. With replacement\nEnter mode: ";
    if (!(cin >> mode) || (mode != 1 && mode != 2)) return 0;
    cout << "Enter number of medicine records (0 to 9): ";
    if (!(cin >> n) || n < 0 || n > 9) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter non-negative medicine key: ";
        if (!(cin >> item.key) || item.key < 0) return 0;
        cout << "Enter medicine name: ";
        if (!getline(cin >> ws, item.name)) return 0;
        cout << "Enter quantity: ";
        if (!(cin >> item.quantity) || item.quantity < 0) return 0;
        insert(table, occupied, item, mode == 2);
    }
    display(table, occupied);
    int key;
    cout << "Enter medicine key to search: ";
    if (!(cin >> key) || key < 0) return 0;
    int index = search(table, occupied, key);
    if (index == -1) cout << "Medicine not found.\n";
    else cout << table[index].name << "\tQuantity: " << table[index].quantity << endl;
    return 0;
}
