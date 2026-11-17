/*
PRACTICE PROBLEM 14: MEDICAL STOCK: LINEAR PROBING HASH TABLE

PROBLEM:
Store medicine keys, names and quantities in a 9-slot hash table using
hash(key) = key % 9 and linear probing for collisions.
The PDF's replacement wording is unclear, so both variants can be selected.

EXAMPLE:
Keys 0 and 9 both belong at index 0, so 9 can use index 1.
Insert key 1: without replacement it uses index 2; with replacement it takes
its home index 1 and moves key 9 to index 2.

HOW TO SOLVE:
1. Select without-replacement or with-replacement mode.
2. Read records and compute each key's home address.
3. If the key exists, update its record instead of storing a duplicate.
4. Find space by checking home, home+1, and so on, wrapping with % 9.
5. Without replacement, store at the first empty slot. With replacement,
   move a foreign home occupant to that slot and put the new key at home.
6. Display the table, then search for a key using the same probe sequence.

VARIABLES / IMPORTANT POINTS:
Use one-word names with cin >>; use underscores for names containing spaces.
table stores records; occupied[i] says whether a slot contains a medicine.
An empty search slot proves the key is absent because deletion is not offered.
Stop after nine probes to avoid circling forever when the table is full.
Keys and quantities must be non-negative; zero is a valid occupied key.
*/

#include <iostream>
#include <string>
using namespace std;

class Medicine
{
public:
    int key, quantity;
    string name;
};

// Keep the data and its operations together in one simple class.
class HashTable
{
public:
    Medicine table[9];
    bool occupied[9]; // All slots start empty.

    // Mark all nine slots unused; record values are read only after their occupied flag is set.
    HashTable() {
        for (int i = 0; i < 9; i++) occupied[i] = false;
    }

    // Probe at most nine positions starting at home; return the matching index or -1.
    int search(int key)
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

    // Update duplicate keys, otherwise find space and apply the selected replacement rule.
    void insert(Medicine item, bool replacement)
    {
        // Check duplicates first: even a full table can update a record already present.
        int existing = search(item.key);
        if (existing != -1)
        {
            table[existing] = item; // Same key: update the medicine's stock.
            return;
        }

        int home = item.key % 9;
        // Keep -1 until an empty slot is found; if it stays -1, no insertion can be made.
        int empty = -1;
        for (int step = 0; step < 9; step++)
        {
            int index = (home + step) % 9;
            if (!occupied[index])
            {
                // Remember the first free slot and stop probing; later slots are unnecessary.
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
            // Preserve the foreign record before overwriting its old position with the new home key.
            table[empty] = table[home];
            table[home] = item;
        }
        else table[empty] = item;
        // The previously free slot now contains a record; an occupied home stays occupied.
        occupied[empty] = true;
    }

    // Print all slots so occupied records and collision positions can be inspected.
    void display()
    {
        cout << "Index\tKey\tMedicine\tQuantity\n";
        for (int i = 0; i < 9; i++)
        {
            cout << i << "\t";
            if (!occupied[i]) cout << "EMPTY\n";
            else cout << table[i].key << "\t" << table[i].name << "\t" << table[i].quantity << endl;
        }
    }

    // Print the record at a successful search index supplied by main().
    void show(int index)
    {
        cout << table[index].name << "\tQuantity: " << table[index].quantity << endl;
    }
};

// Read the probing mode and medicine records, display the table, then perform one search.
int main()
{

    HashTable stock;
    Medicine item;
    int mode, n;
    // The PDF's wording is unclear, so either probing variant can be selected.
    cout << "1. Without replacement  2. With replacement\nEnter mode: ";
    cin >> mode;

    if ((mode != 1 && mode != 2)) return 0;
    cout << "Enter number of medicine records (0 to 9): ";
    cin >> n;

    if (n < 0 || n > 9) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter non-negative medicine key: ";
        cin >> item.key;

        if (item.key < 0) return 0;
        cout << "Enter medicine name: ";
        cin >> item.name;

        cout << "Enter quantity: ";
        cin >> item.quantity;

        if (item.quantity < 0) return 0;
        stock.insert(item, mode == 2);
    }
    stock.display();
    int key;
    cout << "Enter medicine key to search: ";
    cin >> key;

    if (key < 0) return 0;
    int index = stock.search(key);
    if (index == -1) cout << "Medicine not found.\n";
    else stock.show(index);
    return 0;
}
