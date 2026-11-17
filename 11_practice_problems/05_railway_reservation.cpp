/*
PRACTICE PROBLEM 5: RAILWAY RESERVATION USING A CIRCULAR LINKED LIST

PROBLEM:
Manage passenger reservations for one train with 10 seats. Allow booking,
cancelling by reservation ID, and displaying the current passengers.
Use a circular linked list to store reservations.

EXAMPLE:
Book Alice -> ID 1, book Bob -> ID 2. Cancel ID 1 -> only Bob remains.
The remaining last node still links back to the first node.

HOW TO SOLVE:
1. Start with tail = nullptr and size = 0.
2. Booking creates a passenger node with a new, unique ID.
3. Insert after tail and move tail to the new node; tail->next is the head.
4. Cancellation travels around the circle looking for the requested ID.
5. Bypass and delete that node, updating tail if the last node was removed.
6. Display visits the circle once, stopping on return to the first node.
7. Repeat the menu so several bookings and cancellations can be practised.

VARIABLES / IMPORTANT POINTS:
Use one-word names with cin >>; use underscores for names containing spaces.
capacity = 10; size = current bookings; nextId never reuses an old ID.
previous is needed to unlink current during cancellation.
For a single node, next points to itself. Removing it makes tail nullptr.
A full train rejects a booking. An unknown ID reports not found.
*/

#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int id;
    string name;
    Node* next;

    // Store a reservation ID and passenger name; add() will connect the circular link.
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

    // Initialize an empty train, its seat limit, and the first ID to issue.
    Queue() {
        tail = nullptr;
        size = 0;
        capacity = 10;
        nextId = 1;
    }

    // Free reservations automatically when the train object leaves scope.
    ~Queue() {
        clear();
    }

    // There are no passengers exactly when tail has no node to point to.
    bool isEmpty() {
        return tail == nullptr;
    }

    // Compare current reservations with seat capacity before allocating another node.
    bool isFull() {
        return size == capacity;
    }

    // tail points to the last passenger; tail->next points to the first.
    // Create one booking and insert it at the tail while preserving the circle.
    void add(string name)
    {
        if (isFull())
        {
            cout << "All 10 seats are booked.\n";
            return;
        }
        // Allocate a separate passenger record only after confirming a seat is free.
        Node* temp = new Node(nextId, name);
        // Advance the ID even if this passenger is cancelled later, keeping IDs unique.
        nextId++;
        if (isEmpty()) temp->next = temp; // Single node points to itself.
        else
        {
            // The new last node must point to the old head before the old tail is changed.
            temp->next = tail->next;
            // Connect the old last node to the new last node, completing the circle.
            tail->next = temp;
        }
        tail = temp;
        size++;
        cout << "Reservation ID: " << temp->id << endl;
    }

    // Search once around the circle and unlink the matching ID, handling the one-node case.
    void cancel(int id)
    {
        if (isEmpty())
        {
            cout << "Reservation not found.\n";
            return;
        }
        // The node before the head is tail, so cancellation of the first node works too.
        Node* previous = tail;
        Node* current = tail->next;
        do
        {
            if (current->id == id)
            {
                // A node is its own predecessor only in a one-node circle.
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

    // A do-while visits the head first and stops before displaying any passenger twice.
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

    // Break the circular link first, then free nodes using ordinary linear traversal.
    void clear()
    {
        // Break the circle, then delete nodes like an ordinary linked list.
        if (tail != nullptr)
        {
            Node* p = tail->next;
            // Turn the circle into a line; otherwise deletion traversal could return to freed memory.
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

// Run the booking menu; each choice calls the circular list operation for that action.
int main()
{

    Queue train;
    int choice, id;
    string name;

    // A small menu is useful here so we can reserve and cancel repeatedly.
    while (true)
    {
        cout << "\n1. Reserve\n2. Cancel\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 4) break;
        if (choice == 1)
        {
            cout << "Enter passenger name: ";
            cin >> name;

            train.add(name);
        }
        else if (choice == 2)
        {
            cout << "Enter reservation ID: ";
            cin >> id;

            train.cancel(id);
        }
        else if (choice == 3) train.show();
        else cout << "Invalid choice.\n";
    }

    return 0;
}
