#include <iostream>
#include <string>
using namespace std;

// Keep the data and its operations together in one simple class.
class Deque
{
public:
    char deque[100];
    int front = 0;
    int rear = -1;

    void pushRear(char value)
    {
        rear++;
        deque[rear] = value;
    }

    char popFront()
    {
        char value = deque[front];
        front++; // Move the front towards the middle.
        return value;
    }

    char popRear()
    {
        char value = deque[rear];
        rear--; // Move the rear towards the middle.
        return value;
    }

    int size()
    {
        return rear - front + 1;
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
