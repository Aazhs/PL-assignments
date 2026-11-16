#include <iostream>
#include <string>
using namespace std;

class Patient
{
public:
    string name;
    int priority;
};

// Adapted from PL/queue.cpp: front/rear, isEmpty(), isFull(), enqueue(),
// dequeue() and display(). Only insertion changes to respect patient priority.
const int MAX = 100;

class Queue {
    Patient arr[MAX];
    int front;
    int rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return rear == MAX - 1;
    }

    void enqueue(Patient value) {
        if (isFull()) {
            cout << "Queue is full. Cannot insert.\n";
            return;
        }
        if (isEmpty()) front = 0;

        // Keep urgent patients near front. Equal priorities keep arrival order.
        int i = rear;
        while (i >= front && arr[i].priority > value.priority) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = value;
        rear++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue empty.\n";
            return;
        }
        cout << "Serving: " << arr[front].name << endl;
        // Removing the last patient resets both indices, as in queue.cpp.
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
    }

    void display() {
        if (isEmpty()) return;
        for (int i = front; i <= rear; i++) {
            cout << arr[i].name << "\tPriority: " << arr[i].priority << endl;
        }
    }
};

int main()
{
    Queue appointments;
    Patient patient;
    int n;
    cout << "Enter number of patients (0 to 100): ";
    if (!(cin >> n) || n < 0 || n > 100) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter patient name: ";
        if (!getline(cin >> ws, patient.name)) return 0;
        cout << "Priority (1 emergency, 2 urgent, 3 routine): ";
        if (!(cin >> patient.priority) || patient.priority < 1 || patient.priority > 3) return 0;
        appointments.enqueue(patient);
    }
    cout << "Appointments in priority order:\n";
    appointments.display();
    // Demonstrate deletion by serving the next appointment.
    appointments.dequeue();
    cout << "Remaining appointments:\n";
    appointments.display();
    return 0;
}
