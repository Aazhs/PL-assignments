#include <iostream>
#include <utility>
using namespace std;

class Node{
public:
    int data;
    Node *prev, *next;
    Node(int value): data(value), prev(nullptr), next(nullptr){}
};
class Dll{
    Node* head = nullptr;
    Node* tail = nullptr;
    void appendNode(Node* p){
        p->prev = tail; p->next = nullptr;
        if(tail) tail->next = p;
        else head = p;
        tail = p;
    }
public:
    ~Dll(){
        while(head){ Node* p = head; head = head->next; delete p; }
    }
    bool input(){
        int n, value;
        cout << "Enter number of nodes: ";
        if(!(cin >> n) || n < 0) return false;
        cout << "Enter values: ";
        for(int i = 0; i < n; i++){
            if(!(cin >> value)) return false;
            appendNode(new Node(value));
        }
        return true;
    }
    void mergeAlternate(Dll& other){
        Node* p = head;
        Node* q = other.head;
        // Insert one node from the second list after each original first-list node.
        while(p && q){
            Node* nextP = p->next;
            Node* nextQ = q->next;
            p->next = q; q->prev = p; q->next = nextP;
            if(nextP) nextP->prev = q;
            else tail = q;
            p = nextP; q = nextQ;
        }
        // Append leftover nodes so unequal list sizes do not lose data.
        while(q){ Node* next = q->next; appendNode(q); q = next; }
        other.head = other.tail = nullptr;
    }
    void sort(){
        // Swap values to sort while keeping both directions of the links intact.
        for(Node* p = head; p; p = p->next)
            for(Node* q = p->next; q; q = q->next)
                if(p->data > q->data) swap(p->data, q->data);
    }
    void display(){
        for(Node* p = head; p; p = p->next) cout << p->data << " <-> ";
        cout << "NULL\nReverse: ";
        for(Node* p = tail; p; p = p->prev) cout << p->data << " <-> ";
        cout << "NULL\n";
    }
};
int main(){
    Dll a, b;
    cout << "First list:\n"; if(!a.input()) return 0;
    cout << "Second list:\n"; if(!b.input()) return 0;
    a.mergeAlternate(b);
    cout << "Alternate merge: "; a.display();
    a.sort(); cout << "Sorted list: "; a.display();
}
