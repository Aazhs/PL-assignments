#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int id;
    string name;
    Node* next;
};

// tail points to the last passenger; tail->next points to the first.
void reserve(Node*& tail, int& count, int& nextId, string name)
{
    if (count == 10)
    {
        cout << "All 10 seats are booked.\n";
        return;
    }
    Node* temp = new Node{nextId, name, nullptr};
    nextId++;
    if (tail == nullptr) temp->next = temp; // Single node points to itself.
    else
    {
        temp->next = tail->next;
        tail->next = temp;
    }
    tail = temp;
    count++;
    cout << "Reservation ID: " << temp->id << endl;
}

void cancel(Node*& tail, int& count, int id)
{
    if (tail == nullptr)
    {
        cout << "Reservation not found.\n";
        return;
    }
    Node* previous = tail;
    Node* current = tail->next;
    do
    {
        if (current->id == id)
        {
            if (current == previous) tail = nullptr; // Only one node remains.
            else
            {
                previous->next = current->next; // Skip the cancelled node.
                if (current == tail) tail = previous;
            }
            delete current;
            count--;
            cout << "Reservation cancelled.\n";
            return;
        }
        previous = current;
        current = current->next;
    } while (current != tail->next); // Stop after one complete circle.
    cout << "Reservation not found.\n";
}

void display(Node* tail)
{
    if (tail == nullptr)
    {
        cout << "No reservations.\n";
        return;
    }
    Node* p = tail->next;
    do
    {
        cout << p->id << "\t" << p->name << endl;
        p = p->next;
    } while (p != tail->next);
}

int main()
{
    Node* tail = nullptr;
    int count = 0, nextId = 1, choice, id;
    string name;

    // A small menu is useful here so we can reserve and cancel repeatedly.
    while (true)
    {
        cout << "\n1. Reserve\n2. Cancel\n3. Display\n4. Exit\nEnter choice: ";
        if (!(cin >> choice) || choice == 4) break;
        if (choice == 1)
        {
            cout << "Enter passenger name: ";
            if (!getline(cin >> ws, name)) break;
            reserve(tail, count, nextId, name);
        }
        else if (choice == 2)
        {
            cout << "Enter reservation ID: ";
            if (!(cin >> id)) break;
            cancel(tail, count, id);
        }
        else if (choice == 3) display(tail);
        else cout << "Invalid choice.\n";
    }

    // Break the circle, then delete nodes like an ordinary linked list.
    if (tail != nullptr)
    {
        Node* p = tail->next;
        tail->next = nullptr;
        while (p != nullptr)
        {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }
    return 0;
}
