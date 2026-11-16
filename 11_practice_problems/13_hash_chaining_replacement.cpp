#include <iostream>
using namespace std;

// How this program works:
// Home address = score % 12; for example 16 belongs to bucket 4.
// Scores with the same home address are joined by next pointers.
// If another chain occupies a new key's home, move that node to a free slot.
// Example: 16 can occupy slot 6, but inserting 6 later moves 16 elsewhere.

class Node{
public:
    int key, slot;
    Node* next;
    Node(int value, int index): key(value), slot(index), next(nullptr){}
};
// Linked collision chains share 12 table slots (coalesced chaining).
// Replacement ensures that each chain starts at its own home address.
class HashTable{
    Node* table[12] = {};
    int hash(int key){ return (key % 12 + 12) % 12; }
    int freeSlot(int home){
        for(int step = 1; step < 12; step++){
            int index = (home + step) % 12;
            if(!table[index]) return index;
        }
        return -1;
    }
public:
    ~HashTable(){ for(int i = 0; i < 12; i++) delete table[i]; }
    void insert(int key){
        // Calculate the bucket where this key belongs.
        int home = hash(key);
        if(!table[home]){ table[home] = new Node(key, home); return; }
        // Look for an empty slot before changing the table.
        int free = freeSlot(home);
        if(free == -1){ cout << "Hash table full.\n"; return; }
        if(hash(table[home]->key) != home){
            // A foreign-chain node occupies this home: relocate that same node.
            // Incoming next pointers remain valid because the Node address stays the same.
            table[free] = table[home];
            table[free]->slot = free;
            table[home] = new Node(key, home);
        }
        else{
            Node* p = table[home];
            while(p->next) p = p->next;
            table[free] = new Node(key, free);
            p->next = table[free];
        }
    }
    void display(){
        cout << "Index\tScore\tNext index\n";
        for(int i = 0; i < 12; i++){
            cout << i << "\t";
            if(!table[i]) cout << "EMPTY\n";
            else cout << table[i]->key << "\t" << (table[i]->next ? table[i]->next->slot : -1) << "\n";
        }
        cout << "Collision chains:\n";
        for(int i = 0; i < 12; i++){
            if(table[i] && hash(table[i]->key) == i){
                cout << i << ": ";
                for(Node* p = table[i]; p; p = p->next) cout << p->key << " -> ";
                cout << "NULL\n";
            }
        }
    }
};
// Program starts here: run the algorithm and display its result.
int main(){
    HashTable scores;
    int data[12] = {10, 5, 4, 14, 15, 20, 1, 11, 6, 16, 36, 28};
    // Insert in the exact order given in the question.
    for(int key : data) scores.insert(key);
    scores.display();
}
