#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* prev;
    Node* next;

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

    Dll() {
        head = nullptr;
    }

    ~Dll() {
        clear();
    }

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

    bool input()
    {
        int n, value;
        cout << "Enter number of nodes: ";
        if (!(cin >> n) || n < 0) return false;
        cout << "Enter values: ";
        for (int i = 0; i < n; i++)
        {
            if (!(cin >> value)) return false;
            create(value);
        }
        return true;
    }

    void mergeAlternate(Dll& other)
    {
        if (head == nullptr)
        {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node* p = head;
        Node* q = other.head;
        while (p != nullptr && q != nullptr)
        {
            // Save the old links before putting q between p and its next node.
            Node* nextP = p->next;
            Node* nextQ = q->next;
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

    void sort(){
        // Empty and single-node lists already have the correct order.
        if (head == nullptr || head->next == nullptr) return;
        Node *p;
        Node *ptr1, *ptr2, *temp;
        bool swapped = true;

        while(swapped){
            swapped = false;
            p = head;

            while(p->next != nullptr){
                if(p->data > p->next->data){
                    swapped = true;
                    ptr1 = p;
                    ptr2 = ptr1->next;
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

                    p = ptr2;
                }

                p = p->next;
            }
        }
    }

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
