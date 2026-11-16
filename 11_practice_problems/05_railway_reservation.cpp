#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int id;
    string name;
    Node* next;

    Node(int number, string passenger) {
        id = number;
        name = passenger;
        next = nullptr;
    }
};

// Adapted from PL/linked/pizza.cpp: Queue, tail, size, add() and show().
// Cancel by reservation ID is added for the railway application.
class Queue
{
public:
    Node* tail;
    int size;
    int capacity;
    int nextId;

    Queue() {
        tail = nullptr;
        size = 0;
        capacity = 10;
        nextId = 1;
    }

    ~Queue() {
        clear();
    }

    bool isEmpty() {
        return tail == nullptr;
    }

    bool isFull() {
        return size == capacity;
    }

    // tail points to the last passenger; tail->next points to the first.
    void add(string name)
    {
        if (isFull())
        {
            cout << "All 10 seats are booked.\n";
            return;
        }
        Node* temp = new Node(nextId, name);
        nextId++;
        if (isEmpty()) temp->next = temp; // Single node points to itself.
        else
        {
            temp->next = tail->next;
            tail->next = temp;
        }
        tail = temp;
        size++;
        cout << "Reservation ID: " << temp->id << endl;
    }

    void cancel(int id)
    {
        if (isEmpty())
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
                size--;
                cout << "Reservation cancelled.\n";
                return;
            }
            previous = current;
            current = current->next;
        } while (current != tail->next); // Stop after one complete circle.
        cout << "Reservation not found.\n";
    }

    void show()
    {
        if (isEmpty())
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

    void clear()
    {
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
    }
};

int main()
{
    Queue train;
    int choice, id;
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
            train.add(name);
        }
        else if (choice == 2)
        {
            cout << "Enter reservation ID: ";
            if (!(cin >> id)) break;
            train.cancel(id);
        }
        else if (choice == 3) train.show();
        else cout << "Invalid choice.\n";
    }

    return 0;
}
