#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* prev;
    Node* next;
};

void append(Node*& head, int value)
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

bool input(Node*& head)
{
    int n, value;
    cout << "Enter number of nodes: ";
    if (!(cin >> n) || n < 0) return false;
    cout << "Enter values: ";
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> value)) return false;
        append(head, value);
    }
    return true;
}

void mergeAlternate(Node*& first, Node*& second)
{
    if (first == nullptr)
    {
        first = second;
        second = nullptr;
        return;
    }
    Node* p = first;
    Node* q = second;
    while (p != nullptr && q != nullptr)
    {
        // Save the old links before putting q between p and its next node.
        Node* nextP = p->next;
        Node* nextQ = q->next;
        p->next = q;
        q->prev = p;
        q->next = nextP;
        if (nextP != nullptr) nextP->prev = q;

        // If the first list is finished, attach the rest of the second list.
        if (nextP == nullptr)
        {
            q->next = nextQ;
            if (nextQ != nullptr) nextQ->prev = q;
            break;
        }
        p = nextP;
        q = nextQ;
    }
    second = nullptr; // All its nodes now belong to the first list.
}

void sort(Node* head)
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

void display(Node* head)
{
    while (head != nullptr)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void clear(Node* head)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Node* first = nullptr;
    Node* second = nullptr;
    cout << "First list:\n";
    bool valid = input(first);
    if (valid)
    {
        cout << "Second list:\n";
        valid = input(second);
    }
    if (valid)
    {
        mergeAlternate(first, second);
        cout << "Alternate merge: ";
        display(first);
        sort(first);
        cout << "Sorted list: ";
        display(first);
    }
    clear(first);
    clear(second);
    return 0;
}
