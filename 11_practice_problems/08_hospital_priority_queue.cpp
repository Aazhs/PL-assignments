#include <iostream>
#include <string>
using namespace std;

// How this program works:
// Keep the most urgent patient at array index 0.
// Insertion shifts less urgent patients right to make room.
// Serving removes index 0 and shifts the remaining patients left.

struct Patient{
    string name;
    int priority;
};
// Smaller priority number means more urgent; equal priorities keep arrival order.
class PriorityQueue{
    Patient arr[100];
    int count = 0;
public:
    void insert(string name, int priority){
        if(priority < 1 || priority > 3){ cout << "Use priority 1 to 3.\n"; return; }
        if(count == 100){ cout << "Queue full.\n"; return; }
        int i = count - 1;
        // Shift only less urgent patients, preserving ties (FIFO).
        while(i >= 0 && arr[i].priority > priority){ arr[i + 1] = arr[i]; i--; }
        arr[i + 1] = {name, priority}; count++;
    }
    void serve(){
        if(count == 0){ cout << "Queue empty.\n"; return; }
        cout << "Serving: " << arr[0].name << "\n";
        for(int i = 1; i < count; i++) arr[i - 1] = arr[i];
        count--;
    }
    void display(){
        if(count == 0) cout << "Queue empty.\n";
        for(int i = 0; i < count; i++) cout << arr[i].name << "\tPriority: " << arr[i].priority << "\n";
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    PriorityQueue patients;
    int choice, priority; string name;
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Hospital Menu =====\n1. Add appointment\n2. Serve next patient\n3. Display\n4. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 4) break;
        switch(choice){
            case 1:
                cout << "Enter name: "; if(!getline(cin >> ws, name)) return 0;
                cout << "Priority (1 emergency, 2 urgent, 3 routine): ";
                if(!(cin >> priority)) return 0;
                patients.insert(name, priority); break;
            case 2: patients.serve(); break;
            case 3: patients.display(); break;
            default: cout << "Invalid choice.\n";
        }
    }
}
