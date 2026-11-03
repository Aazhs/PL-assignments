#include <iostream>
using namespace std;

const int MAX = 5;

// Deque (Double Ended Queue): we can insert and delete at BOTH ends.
// Built on a circular array, so front/rear wrap around using % MAX.
//   - push/pop at rear  -> rear moves forward / backward
//   - push/pop at front -> front moves backward / forward
class Deque {
    int arr[MAX];
    int front;  // index of the first element (-1 when empty)
    int rear;   // index of the last element (-1 when empty)
    int count;  // number of elements

public:
    Deque() {
        front = -1;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX;
    }

    void pushFront(int value) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at front.\n";
            return;
        }
        // First element: front and rear both point to slot 0
        if (isEmpty()) {
            front = rear = 0;
        } else {
            // Move front one step back; adding MAX avoids a negative value (index 0 wraps to MAX-1)
            front = (front - 1 + MAX) % MAX;
        }
        arr[front] = value;
        count++;
        cout << value << " inserted at front.\n";
    }

    void pushRear(int value) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at rear.\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            // Move rear one step forward, wrapping to 0 after the last index
            rear = (rear + 1) % MAX;
        }
        arr[rear] = value;
        count++;
        cout << value << " inserted at rear.\n";
    }

    void popFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from front.\n";
            return;
        }
        // We don't erase the value; moving 'front' forward is enough to remove it
        cout << arr[front] << " deleted from front.\n";
        count--;
        // Deque became empty, so reset both indices
        if (isEmpty()) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
    }

    void popRear() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from rear.\n";
            return;
        }
        cout << arr[rear] << " deleted from rear.\n";
        count--;
        if (isEmpty()) {
            front = rear = -1;
        } else {
            // Move rear one step back with wrap-around
            rear = (rear - 1 + MAX) % MAX;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty.\n";
            return;
        }
        cout << "Deque elements (front -> rear): ";
        // Visit 'count' items starting at front, wrapping around the array
        for (int i = 0, idx = front; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % MAX;
        }
        cout << "\n";
    }
};

// Menu-driven program to test all deque operations
int main() {
    Deque dq;
    int choice, value;

    do {
        cout << "\n===== DEQUE MENU =====\n";
        cout << "1. Insert at Front\n";
        cout << "2. Insert at Rear\n";
        cout << "3. Delete from Front\n";
        cout << "4. Delete from Rear\n";
        cout << "5. Display\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Non-number entered: clear the error state and throw away the bad input
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                dq.pushFront(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                dq.pushRear(value);
                break;
            case 3:
                dq.popFront();
                break;
            case 4:
                dq.popRear();
                break;
            case 5:
                dq.display();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
