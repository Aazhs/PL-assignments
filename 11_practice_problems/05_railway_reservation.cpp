#include <iostream>
#include <string>
using namespace std;

// How this program works:
// A circular list has no NULL at the end: the last node links to the head.
// Reserve: add a passenger at the end. Cancel: unlink the matching ID.
// Use a do-while traversal so the first passenger is visited exactly once.

class Node{
public:
    int id;
    string name;
    Node* next;
    Node(int number, string passenger): id(number), name(passenger), next(nullptr){}
};
// The last passenger points back to the first: tail->next is the head.
class Railway{
    Node* tail = nullptr;
    int count = 0, nextId = 1;
public:
    ~Railway(){
        if(!tail) return;
        Node* p = tail->next;
        tail->next = nullptr; // Break the circle before freeing nodes.
        while(p){ Node* temp = p; p = p->next; delete temp; }
    }
    void reserve(string name){
        if(count == 10){ cout << "All 10 seats are booked.\n"; return; }
        Node* p = new Node(nextId++, name);
        if(!tail) p->next = p;
        else{ p->next = tail->next; tail->next = p; }
        tail = p;
        count++;
        cout << "Reservation ID: " << p->id << "\n";
    }
    void cancel(int id){
        if(tail){
            Node* previous = tail;
            Node* p = tail->next;
            do{
                if(p->id == id){
                    if(p == previous) tail = nullptr;
                    else{
                        previous->next = p->next;
                        if(p == tail) tail = previous;
                    }
                    delete p;
                    count--;
                    cout << "Reservation cancelled.\n"; return;
                }
                previous = p;
                p = p->next;
            }while(p != tail->next);
        }
        cout << "Reservation not found.\n";
    }
    void display(){
        if(!tail){ cout << "No reservations.\n"; return; }
        Node* p = tail->next;
        do{ cout << p->id << "\t" << p->name << "\n"; p = p->next; }while(p != tail->next);
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    Railway train;
    int choice, id; string name;
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Railway Menu =====\n1. Reserve\n2. Cancel\n3. Display\n4. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 4) break;
        switch(choice){
            case 1:
                cout << "Enter passenger name: ";
                if(!getline(cin >> ws, name)) return 0;
                train.reserve(name); break;
            case 2:
                cout << "Enter reservation ID: ";
                if(!(cin >> id)) return 0;
                train.cancel(id); break;
            case 3: train.display(); break;
            default: cout << "Invalid choice.\n";
        }
    }
}
