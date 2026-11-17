/*
PRACTICE PROBLEM 4: ALTERNATE MERGE AND SORT OF DOUBLY LINKED LISTS

PROBLEM:
Insert nodes of a second doubly linked list at alternate positions in the
first list. Then sort the merged list in ascending order.

EXAMPLE:
First = 5 1, second = 4 2 3
Alternate merge = 5 4 1 2 3; sorted answer = 1 2 3 4 5.

HOW TO SOLVE:
1. Create both lists. Each node has data, next and prev pointers.
2. Let p visit the first list and q visit the second list.
3. Save their next pointers before inserting q immediately after p.
4. Repair both forward and backward links; move to the saved next nodes.
5. If the first list ends earlier, attach the rest of the second list.
6. Sort using the neighbouring-node swaps from the original PL Dll code.
7. Display the list before and after sorting.

VARIABLES / IMPORTANT POINTS:
nextP and nextQ preserve addresses that would otherwise be overwritten.
ptr1 and ptr2 are neighbouring nodes being swapped during sort.
The merged list owns the original nodes; other.head becomes nullptr.
If the first list is empty it takes the second list. Empty lists sort safely.
*/

#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* prev;
    Node* next;

    // Initialize both links to nullptr so a newly created node is not attached to any list.
    Node() {
        data = 0;
        prev = nullptr;
        next = nullptr;
    }
};

// Adapted from PL/linked/doubly.cpp: Dll, create(), display() and sort().
// The merge operation alternates nodes as required by this practice problem.
class Dll
{
public:
    Node* head;

    // Start with an empty head; the first create() call will set it.
    Dll() {
        head = nullptr;
    }

    // Call clear() automatically when this list leaves scope, freeing the nodes it owns.
    ~Dll() {
        clear();
    }

    // Walk to the last node, attach the new value, and connect its backward link too.
    void create(int value)
    {
        Node* temp = new Node();
        temp->data = value;
        if (head == nullptr)
        {
            head = temp;
            return;
        }
        Node* p = head;
        while (p->next != nullptr) p = p->next;
        p->next = temp;
        temp->prev = p; // Always connect both directions.
    }

    // Read how many nodes to create, then append each value in the entered order.
    bool input()
    {

        int n, value;
        cout << "Enter number of nodes: ";
        cin >> n;

        if (n < 0) return false;
        cout << "Enter values: ";
        for (int i = 0; i < n; i++)
        {
            cin >> value;

            create(value);
        }
        return true;
    }

    // Relink existing nodes; do not copy values or allocate a second set of nodes.
    void mergeAlternate(Dll& other)
    {
        if (head == nullptr)
        {
            head = other.head;
            other.head = nullptr;
            return;
        }
        // p and q move through the original lists independently, one node from each per round.
        Node* p = head;
        Node* q = other.head;
        while (p != nullptr && q != nullptr)
        {
            // Save the old links before putting q between p and its next node.
            Node* nextP = p->next;
            Node* nextQ = q->next;
            // After insertion the local order will be p <-> q <-> nextP.
            p->next = q;
            q->prev = p;
            q->next = nextP;
            if (nextP != nullptr) nextP->prev = q;

            // If this list is finished, attach the rest of the other list.
            if (nextP == nullptr)
            {
                q->next = nextQ;
                if (nextQ != nullptr) nextQ->prev = q;
                break;
            }
            p = nextP;
            q = nextQ;
        }
        other.head = nullptr; // All its nodes now belong to this list.
    }

    // Repeatedly swap out-of-order neighbours until a complete pass makes no swap.
    void sort(){
        // Empty and single-node lists already have the correct order.
        if (head == nullptr || head->next == nullptr) return;
        Node *p;
        Node *ptr1, *ptr2, *temp;
        // Start with true to force one pass; a pass without swaps proves the list is sorted.
        bool swapped = true;

        while(swapped){
            // Reset for this pass. Any out-of-order neighbour pair will set it true again.
            swapped = false;
            p = head;

            while(p->next != nullptr){
                if(p->data > p->next->data){
                    swapped = true;
                    ptr1 = p;
                    ptr2 = ptr1->next;
                    // Remember the node after the pair so the pair can be reversed without losing the rest.
                    temp = ptr2->next;

                    // Reconnect the node before the swapped pair (or update head).
                    if(ptr1->prev == nullptr){
                        head = ptr2;
                    }
                    else{
                        ptr1->prev->next = ptr2;
                    }

                    // Swap neighbouring nodes, fixing both next and prev links.
                    ptr2->next = ptr1;
                    ptr2->prev = ptr1->prev;
                    ptr1->prev = ptr2;
                    ptr1->next = temp;

                    // Repair the back link of the node after the pair.
                    if(temp != nullptr){
                        temp->prev = ptr1;
                    }

                    // After the swap, ptr2 comes first; the advance below lands on ptr1 for its next comparison.
                    p = ptr2;
                }

                p = p->next;
            }
        }
    }

    // Follow next pointers using a local cursor so printing does not change head.
    void display()
    {
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Delete nodes from the front until none remain; head finishes as nullptr.
    void clear()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Read both lists, alternate their nodes, show that merge, then sort and show the result.
int main()
{
    Dll first, second;
    cout << "First list:\n";
    bool valid = first.input();
    if (valid)
    {
        cout << "Second list:\n";
        valid = second.input();
    }
    if (valid)
    {
        first.mergeAlternate(second);
        cout << "Alternate merge: ";
        first.display();
        first.sort();
        cout << "Sorted list: ";
        first.display();
    }
    return 0;
}
