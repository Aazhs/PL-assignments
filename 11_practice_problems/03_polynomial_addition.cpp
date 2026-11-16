#include <iostream>
#include <cmath>
using namespace std;

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
        while(head){ Node* temp = head; head = head->next; delete temp; }
    }
    void insert(double c, int e){
        if(c == 0) return;
        // Keep exponents descending and combine repeated exponents.
        Node** link = &head;
        while(*link && (*link)->exponent > e) link = &(*link)->next;
        if(*link && (*link)->exponent == e){
            (*link)->coefficient += c;
            if((*link)->coefficient == 0){
                Node* temp = *link; *link = temp->next; delete temp;
            }
        }
        else{
            Node* temp = new Node(c, e);
            temp->next = *link; *link = temp;
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
int main(){
    Polynomial a, b, result;
    cout << "First polynomial:\n";
    if(!a.input()) return 0;
    cout << "Second polynomial:\n";
    if(!b.input()) return 0;
    a.add(b, result);
    cout << "Sum: "; result.display();
}
