#include <iostream>
#include <cmath>
using namespace std;

// How this program works:
// Example: (2x^2 + 3) + (5x^2 + x) = 7x^2 + x + 3.
// Each node stores just one term; next points to the following term.
// Insert terms from both inputs into the result, combining matching powers.

// One linked-list node stores one coefficient and exponent.
class Node{
public:
    double coefficient;
    int exponent;
    Node* next;
    Node(double c, int e): coefficient(c), exponent(e), next(nullptr){}
};
class Polynomial{
    Node* head = nullptr;
public:
    ~Polynomial(){
        while(head){ Node* temp = head;
            head = head->next;
            delete temp; }
    }
    void insert(double c, int e){
        if(c == 0) return;
        // Walk with two ordinary pointers: current and the node before it.
        // Stop where the new exponent belongs in descending order.
        Node* current = head;
        Node* previous = nullptr;
        while(current != nullptr && current->exponent > e){
            previous = current;
            current = current->next;
        }

        if(current != nullptr && current->exponent == e){
            // Same power: add coefficients, e.g. 2x^3 + 5x^3 = 7x^3.
            current->coefficient += c;
            if(current->coefficient == 0){
                // Opposite terms cancel. Remove the node from the chain.
                if(previous == nullptr) head = current->next;
                else previous->next = current->next;
                delete current;
            }
        }
        else{
            // Different power: place a new node between previous and current.
            Node* temp = new Node(c, e);
            temp->next = current;
            if(previous == nullptr) head = temp;
            else previous->next = temp;
        }
    }

    bool input(){
        int n, e; double c;
        cout << "Enter number of terms: ";
        if(!(cin >> n) || n < 0) return false;
        cout << "Enter coefficient and exponent for each term:\n";
        for(int i = 0; i < n; i++){
            if(!(cin >> c >> e) || e < 0) return false;
            insert(c, e);
        }
        return true;
    }
    void add(Polynomial& other, Polynomial& result){
        for(Node* p = head; p; p = p->next) result.insert(p->coefficient, p->exponent);
        for(Node* p = other.head; p; p = p->next) result.insert(p->coefficient, p->exponent);
    }
    void display(){
        if(!head) cout << "0";
        for(Node* p = head; p; p = p->next){
            if(p != head) cout << (p->coefficient < 0 ? " - " : " + ");
            else if(p->coefficient < 0) cout << "-";
            cout << abs(p->coefficient);
            if(p->exponent != 0) cout << "x^" << p->exponent;
        }
        cout << "\n";
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    Polynomial a, b, result;
    cout << "First polynomial:\n";
    if(!a.input()) return 0;
    cout << "Second polynomial:\n";
    if(!b.input()) return 0;
    a.add(b, result);
    cout << "Sum: "; result.display();
}
