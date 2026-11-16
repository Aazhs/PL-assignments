#include <iostream>
using namespace std;

struct Node
{
    int key, slot;
    Node* next;
};

int freeSlot(Node* table[], int home)
{
    // Start after home, wrap at slot 12, and stop at the first empty slot.
    for (int step = 1; step < 12; step++)
    {
        int index = (home + step) % 12;
        if (table[index] == nullptr) return index;
    }
    return -1;
}

void insert(Node* table[], int key)
{
    int home = key % 12;
    if (table[home] == nullptr)
    {
        table[home] = new Node{key, home, nullptr};
        return;
    }

    int empty = freeSlot(table, home);
    if (empty == -1)
    {
        cout << "Hash table full.\n";
        return;
    }

    if (table[home]->key % 12 != home)
    {
        // A key from another chain occupies this slot. Move its node.
        // Example: 16 may be in slot 6, but key 6 needs that home slot.
        table[empty] = table[home];
        table[empty]->slot = empty;
        table[home] = new Node{key, home, nullptr};
        // Other nodes still point to the same relocated Node object.
    }
    else
    {
        // Same home: add the new node at the end of this collision chain.
        Node* p = table[home];
        while (p->next != nullptr) p = p->next;
        table[empty] = new Node{key, empty, nullptr};
        p->next = table[empty];
    }
}

void display(Node* table[])
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

int main()
{
    Node* table[12] = {};
    int scores[12] = {10, 5, 4, 14, 15, 20, 1, 11, 6, 16, 36, 28};
    // Insert the given scores in their original order.
    for (int i = 0; i < 12; i++) insert(table, scores[i]);
    display(table);
    // Every table slot owns one node, so delete each node once.
    for (int i = 0; i < 12; i++) delete table[i];
    return 0;
}
