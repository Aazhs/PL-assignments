/*
PRACTICE PROBLEM 13: BATSMAN SCORES: LINKED HASH CHAINS WITH REPLACEMENT

PROBLEM:
Insert the scores 10, 5, 4, 14, 15, 20, 1, 11, 6, 16, 36, 28 into a
12-slot hash table using hash(key) = key % 12 and linked collision chains.
The question calls this "separate chaining with replacement"; this program
uses linked chains sharing table slots (coalesced chaining) to show replacement.

EXAMPLE:
4, 16 and 28 all have home address 4, so they belong to the chain
4 -> 16 -> 28. If 16 occupies slot 6, inserting key 6 moves 16 elsewhere.

HOW TO SOLVE:
1. Start with all 12 table pointers set to nullptr (empty).
2. Compute home = key % 12. If home is empty, put a new node there.
3. Otherwise find an empty slot by scanning forward with wraparound.
4. If the occupant belongs to home, append the new node to that chain.
5. If the occupant belongs elsewhere, move its pointer to the free slot,
   update its stored slot number, and put the new key at its own home.
6. Print table indices, keys, next indices and the linked collision chains.

VARIABLES / IMPORTANT POINTS:
table[i] points to the node occupying slot i; node.slot records that index.
node.next joins scores with the same home. -1 in the output ends a chain.
Replacement moves a pointer, not the Node object, so incoming links stay valid.
A full table rejects insertion; clear() deletes each allocated node once.
*/

#include <iostream>
using namespace std;

class Node
{
public:
    int key, slot;
    Node* next;

    // Create a score node recording its physical table slot and an initially empty chain link.
    Node(int value, int index) {
        key = value;
        slot = index;
        next = nullptr;
    }
};

// Keep the data and its operations together in one simple class.
class HashTable
{
public:
    Node* table[12];

    // Initialize every pointer to nullptr so freeSlot() can recognize unused positions.
    HashTable() {
        for (int i = 0; i < 12; i++) table[i] = nullptr;
    }

    // Scan at most the other eleven slots, wrapping around; return -1 if none is empty.
    int freeSlot(int home)
    {
        // Start after home, wrap at slot 12, and stop at the first empty slot.
        for (int step = 1; step < 12; step++)
        {
            int index = (home + step) % 12;
            if (table[index] == nullptr) return index;
        }
        return -1;
    }

    // Resolve a collision either by extending the home chain or relocating a foreign occupant.
    void insert(int key)
    {
        // This home is the chain identifier; collision nodes may physically occupy other indices.
        int home = key % 12;
        if (table[home] == nullptr)
        {
            table[home] = new Node(key, home);
            return;
        }

        // Find space before modifying any existing pointer, so a full table changes nothing.
        int empty = freeSlot(home);
        if (empty == -1)
        {
            cout << "Hash table full.\n";
            return;
        }

        if (table[home]->key % 12 != home)
        {
            // A key from another chain occupies this slot. Move its node.
            // Example: 16 may be in slot 6, but key 6 needs that home slot.
            // Move the pointer to the existing node, preserving every next link that refers to it.
            table[empty] = table[home];
            // Update its physical-index label so displayed next indices still point to the correct slot.
            table[empty]->slot = empty;
            table[home] = new Node(key, home);
            // Other nodes still point to the same relocated Node object.
        }
        else
        {
            // Same home: add the new node at the end of this collision chain.
            Node* p = table[home];
            while (p->next != nullptr) p = p->next;
            table[empty] = new Node(key, empty);
            // Link the old chain tail to the new collision node without mixing different home chains.
            p->next = table[empty];
        }
    }

    // Print physical slots first, then logical chains beginning only at their home nodes.
    void display()
    {
        cout << "Index\tScore\tNext index\n";
        for (int i = 0; i < 12; i++)
        {
            cout << i << "\t";
            if (table[i] == nullptr) cout << "EMPTY\n";
            else
            {
                cout << table[i]->key << "\t";
                if (table[i]->next == nullptr) cout << -1;
                else cout << table[i]->next->slot;
                cout << endl;
            }
        }
        cout << "Collision chains:\n";
        for (int i = 0; i < 12; i++)
        {
            // Print only from a chain's home, not from its overflow nodes.
            if (table[i] != nullptr && table[i]->key % 12 == i)
            {
                cout << i << ": ";
                Node* p = table[i];
                while (p != nullptr)
                {
                    cout << p->key << " -> ";
                    p = p->next;
                }
                cout << "NULL\n";
            }
        }
    }

    // Delete each table-owned node exactly once and reset its slot pointer to nullptr.
    void clear()
    {
        // Each table slot owns one node; next pointers do not own extra nodes.
        for (int i = 0; i < 12; i++)
        {
            delete table[i];
            table[i] = nullptr;
        }
    }
};

// Insert the fixed twelve scores in order, show the table/chains, and release the nodes.
int main()
{
    HashTable table;
    int scores[12] = {10, 5, 4, 14, 15, 20, 1, 11, 6, 16, 36, 28};
    // Insert the given scores in their original order.
    for (int i = 0; i < 12; i++) table.insert(scores[i]);
    table.display();
    // Every table slot owns one node, so delete each node once.
    table.clear();
    return 0;
}
