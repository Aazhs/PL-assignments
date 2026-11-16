#include <iostream>
#include <string>
using namespace std;

// Each end of this array acts as one end of a double ended queue.
class Deque{
    char* data;
    int front = 0, rear = -1;
public:
    Deque(int capacity){ data = new char[capacity]; }
    ~Deque(){ delete[] data; }
    void pushRear(char c){ data[++rear] = c; }
    char popFront(){ return data[front++]; }
    char popRear(){ return data[rear--]; }
    int size(){ return rear - front + 1; }
};
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
