#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* prev;
    Node* next;
};

// Keep the data and its operations together in one simple class.
class DoublyLinkedList
{
public:
    Node* head = nullptr;

    void append(int value)
    {
        Node* temp = new Node{value, nullptr, nullptr};
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
            append(value);
        }
        return true;
    }

    void mergeAlternate(DoublyLinkedList& other)
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

    void sort()
    {
        // Compare each value with the values after it; swap if out of order.
        for (Node* p = head; p != nullptr; p = p->next)
            for (Node* q = p->next; q != nullptr; q = q->next)
                if (p->data > q->data)
                {
                    int temp = p->data;
                    p->data = q->data;
                    q->data = temp;
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
    DoublyLinkedList first, second;
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
    first.clear();
    second.clear();
    return 0;
}
