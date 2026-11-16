#include <iostream>
#include <string>
using namespace std;

// Adapted from PL/stack/deque.cpp: the array now stores characters.
const int MAX = 100;
class Deque {
    char arr[MAX];
    int front;
    int rear;
    int count;

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

    // Adding MAX avoids a negative index when front wraps around.
    void pushFront(char value) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at front.\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            front = (front - 1 + MAX) % MAX;
        }
        arr[front] = value;
        count++;
        // Character stored; no extra output during palindrome checking.
    }

    void pushRear(char value) {
        if (isFull()) {
            cout << "Deque is full. Cannot insert at rear.\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }
        arr[rear] = value;
        count++;
        // Character stored; compare it later from either end.
    }

    // Return the removed character so the caller can compare the pair.
    char popFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from front.\n";
            return '\0';
        }
        char value = arr[front];
        count--;
        if (isEmpty()) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
        return value;
    }

    char popRear() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from rear.\n";
            return '\0';
        }
        char value = arr[rear];
        count--;
        if (isEmpty()) {
            front = rear = -1;
        } else {
            rear = (rear - 1 + MAX) % MAX;
        }
        return value;
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty.\n";
            return;
        }
        cout << "Deque elements (front -> rear): ";
        for (int i = 0, idx = front; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % MAX;
        }
        cout << "\n";
    }
    int size() {
        return count;
    }
};

bool palindrome(string text)
{
    Deque letters;
    for (int i = 0; i < int(text.size()); i++)
        letters.pushRear(text[i]);

    // A deque lets us remove characters from both ends.
    // For "madam": m matches m, a matches a, then only d remains.
    while (letters.size() > 1)
    {
        char first = letters.popFront();
        char last = letters.popRear();
        if (first != last) return false;
    }
    return true; // No mismatches; empty and one-character strings also pass.
}

int main()
{
    string text;
    cout << "Enter string (up to 100 characters): ";
    if (!getline(cin, text) || text.size() > 100) return 0;
    // Compare exactly as entered, including spaces and letter case.
    if (palindrome(text)) cout << "Palindrome.\n";
    else cout << "Not a palindrome.\n";
    return 0;
}
