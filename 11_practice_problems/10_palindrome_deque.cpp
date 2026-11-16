#include <iostream>
#include <string>
using namespace std;

// How this program works:
// Put the string characters into a double ended queue.
// Remove one character from each end and compare them.
// A mismatch means not a palindrome; matching pairs continue inward.
// Example: madam -> m matches m, a matches a, middle d is left alone.

// Each end of this array acts as one end of a double ended queue.
class Deque{
    char* data;
    int front = 0, rear = -1; // rear < front means the deque is empty.
public:
    Deque(int capacity){ data = new char[capacity]; }
    ~Deque(){ delete[] data; }
    void pushRear(char c){ data[++rear] = c; }
    // Read the first character, then move front one position right.
    char popFront(){ return data[front++]; }
    // Read the last character, then move rear one position left.
    char popRear(){ return data[rear--]; }
    int size(){ return rear - front + 1; }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    string text;
    cout << "Enter string: ";
    if(!getline(cin, text)) return 0;
    Deque letters(static_cast<int>(text.size()));
    // Compare exactly as entered: spaces and letter case are significant.
    for(char c : text) letters.pushRear(c);
    bool palindrome = true;
    while(letters.size() > 1){
        char first = letters.popFront();
        char last = letters.popRear();
        if(first != last){ palindrome = false; break; }
    }
    cout << (palindrome ? "Palindrome.\n" : "Not a palindrome.\n");
}
