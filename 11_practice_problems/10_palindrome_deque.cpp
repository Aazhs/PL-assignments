/*
PRACTICE PROBLEM 10: PALINDROME CHECK USING A DEQUE

PROBLEM:
Check whether a string reads the same forward and backward by using a deque
(double ended queue), which supports removal at both ends.

EXAMPLE:
madam -> compare m with m, then a with a; the middle d needs no comparison.
madam is a palindrome; hello is not.

HOW TO SOLVE:
1. Read one word and insert every character at the rear of a circular deque.
2. While at least two characters remain, remove one from each end.
3. If that pair differs, return false immediately.
4. If all pairs match, return true and print Palindrome.

VARIABLES / IMPORTANT POINTS:
arr holds characters; front/rear mark the ends; count tracks stored characters.
% MAX wraps movement around the circular array (MAX = 100).
Input is one word, with case-sensitive comparison; cin >> stops at whitespace.
The algorithm also handles an empty string, but the console input expects a word.
pushFront() and display() are retained from the original deque implementation;
this application only needs pushRear(), popFront(), popRear() and size().
*/

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
    // Initialize the empty end indices and zero count before any character is inserted.
    Deque() {
        front = -1;
        rear = -1;
        count = 0;
    }

    // Use count so a wrapped circular array still has an unambiguous empty condition.
    bool isEmpty() {
        return count == 0;
    }

    // Prevent an insertion from overwriting characters when every slot is occupied.
    bool isFull() {
        return count == MAX;
    }

    // Adding MAX avoids a negative index when front wraps around.
    // Move front one step backwards with wraparound and store a character there.
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
        // One more character is stored; count distinguishes a full circle from an empty deque.
        count++;
        // Character stored; no extra output during palindrome checking.
    }

    // Move rear one step forwards with wraparound and store the next input character.
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
    // Save the first character, advance front, and return the saved value for comparison.
    char popFront() {
        if (isEmpty()) {
            cout << "Deque is empty. Cannot delete from front.\n";
            return '\0';
        }
        // Save before changing the front index; this is the character the caller should receive.
        char value = arr[front];
        count--;
        if (isEmpty()) {
            front = rear = -1;
        } else {
            // Move towards the next character; index MAX-1 wraps back to 0.
            front = (front + 1) % MAX;
        }
        return value;
    }

    // Save the last character, retreat rear, and return the saved value for comparison.
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
            // Adding MAX keeps the result non-negative when rear was 0.
            rear = (rear - 1 + MAX) % MAX;
        }
        return value;
    }

    // Follow count circular positions starting at front, rather than assuming front <= rear.
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
    // Return how many characters remain; the palindrome loop stops at zero or one.
    int size() {
        return count;
    }
};

// Load a local deque, then compare and remove matching pairs from opposite ends.
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
        // A single unequal pair proves that the original string cannot read the same backwards.
        if (first != last) return false;
    }
    return true; // No mismatches; empty and one-character strings also pass.
}

// Read one word, check its length, and print the result of the deque comparison.
int main()
{

    string text;
    cout << "Enter string (up to 100 characters): ";
    cin >> text;

    if (text.size() > 100) return 0;
    // Compare the input word exactly as entered, including letter case.
    if (palindrome(text)) cout << "Palindrome.\n";
    else cout << "Not a palindrome.\n";
    return 0;
}
