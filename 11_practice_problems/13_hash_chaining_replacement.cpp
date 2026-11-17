/*
QUESTION 13: HASHING WITH CHAINS AND REPLACEMENT

Problem: Store the given 12 scores using score % 12.
If scores have the same home position, connect them in a chain.

Simple idea: Use two arrays inside one class. No Node class or pointers.
table[i] stores a score. next[i] stores the index of the next chain entry.
-1 means an empty slot in table, or the end of a chain in next.
This is an index-based linked list (a chain stored inside arrays).

Steps:
1. Compute home = value % 12. If empty, store the score there.
2. Otherwise find a free slot by moving forward and wrapping around.
3. If the home occupant belongs there, add the score at the chain's end.
4. If it belongs elsewhere, move it to the free slot, repair its old chain,
   and give the home position to the new score.
5. Display each score and the next index.

Example: Insert 4, 16, 5. Initially 4 uses slot 4 and 16 uses slot 5.
When 5 arrives, move 16 to slot 6 and change next[4] to 6.
Now slot 5 stores 5, and the chain of 4 still reaches 16.
*/
#include <iostream>
using namespace std;

class HashTable
{
public:
    int table[12], next[12];

    HashTable()
    {
        for (int i = 0; i < 12; i++)
        {
            table[i] = -1;
            next[i] = -1;
        }
    }

    void insert(int value)
    {
        int home = value % 12;
        if (table[home] == -1)
        {
            table[home] = value;
            return;
        }

        // Find an empty position, checking no more than one full circle.
        int empty = (home + 1) % 12;
        while (empty != home && table[empty] != -1)
            empty = (empty + 1) % 12;
        if (empty == home)
        {
            cout << "Table full.\n";
            return;
        }

        if (table[home] % 12 == home)
        {
            // Follow next indices to the chain's last score, then attach.
            int p = home;
            while (next[p] != -1) p = next[p];
            next[p] = empty;
            table[empty] = value;
        }
        else
        {
            // Find the entry that links to this misplaced occupant.
            int p = table[home] % 12;
            while (next[p] != home) p = next[p];

            // Move the occupant AND its onward link; repair the incoming link.
            table[empty] = table[home];
            next[empty] = next[home];
            next[p] = empty;
            table[home] = value;
            next[home] = -1;
        }
    }

    void display()
    {
        cout << "Index\tScore\tNext\n";
        for (int i = 0; i < 12; i++)
            cout << i << "\t" << table[i] << "\t" << next[i] << endl;
    }
};

int main()
{
    HashTable h;
    int scores[12] = {10, 5, 4, 14, 15, 20, 1, 11, 6, 16, 36, 28};
    for (int i = 0; i < 12; i++) h.insert(scores[i]);
    h.display();
    return 0;
}
