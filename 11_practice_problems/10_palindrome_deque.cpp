#include <iostream>
#include <string>
using namespace std;

void pushRear(char deque[], int& rear, char value)
{
    rear++;
    deque[rear] = value;
}

char popFront(char deque[], int& front)
{
    char value = deque[front];
    front++; // Move the front towards the middle.
    return value;
}

char popRear(char deque[], int& rear)
{
    char value = deque[rear];
    rear--; // Move the rear towards the middle.
    return value;
}

bool palindrome(string text)
{
    char deque[100];
    int front = 0, rear = -1;
    for (int i = 0; i < int(text.size()); i++)
        pushRear(deque, rear, text[i]);

    // A deque lets us remove characters from both ends.
    // For "madam": m matches m, a matches a, then only d remains.
    while (front < rear)
    {
        char first = popFront(deque, front);
        char last = popRear(deque, rear);
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
