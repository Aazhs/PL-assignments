/*
PRACTICE PROBLEM 8: HOSPITAL APPOINTMENTS USING A PRIORITY QUEUE

PROBLEM:
Manage patient appointments with a priority queue. More urgent patients
must be served before routine patients, even if they arrive later.

EXAMPLE:
Alice (3), Bob (1), Cara (1) enter in that order.
Service order is Bob, Cara, Alice. Bob stays before Cara because he arrived first.

HOW TO SOLVE:
1. Read each patient's name and priority: 1 emergency, 2 urgent, 3 routine.
2. enqueue() inserts the patient into an array ordered by priority.
3. Move less urgent patients one place right to make room.
4. Leave equal priorities in arrival order by shifting only larger priorities.
5. Display the appointments, dequeue one patient, then display the remaining queue.

VARIABLES / IMPORTANT POINTS:
arr stores Patient objects. front points to the next patient; rear to the last.
front == -1 means empty. Initially front and rear are both -1.
dequeue() advances front instead of shifting the whole array.
The final deletion resets both indices. The linear array holds 100 appointments.
*/

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
    // Initialize front and rear to -1 to mark a queue with no appointments.
    Queue() {
        front = -1;
        rear = -1;
    }

    // Test the empty marker before attempting to remove or display a patient.
    bool isEmpty() {
        return front == -1;
    }

    // The linear queue cannot insert beyond its final array position.
    bool isFull() {
        return rear == MAX - 1;
    }

    // Insert by urgency using shifts; the comparison preserves arrival order for ties.
    void enqueue(Patient value) {
        if (isFull()) {
            cout << "Queue is full. Cannot insert.\n";
            return;
        }
        if (isEmpty()) front = 0;

        // Keep urgent patients near front. Equal priorities keep arrival order.
        // Start comparisons at the last waiting patient and walk backwards towards front.
        int i = rear;
        while (i >= front && arr[i].priority > value.priority) {
            // Move this less urgent record right; its old slot can now be filled from the left.
            arr[i + 1] = arr[i];
            i--;
        }
        // The loop stops just before the correct position for the new patient.
        arr[i + 1] = value;
        rear++;
    }

    // Serve arr[front], then advance front or reset both indices if that was the last patient.
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
            // The served record is ignored from now on; display begins at the new front.
            front++;
        }
    }

    // Print only the active region front through rear, omitting already served patients.
    void display() {
        if (isEmpty()) return;
        for (int i = front; i <= rear; i++) {
            cout << arr[i].name << "\tPriority: " << arr[i].priority << endl;
        }
    }
};

// Read the appointments, show their priority order, serve the first, and show who remains.
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
