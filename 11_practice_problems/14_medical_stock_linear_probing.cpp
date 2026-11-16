#include <iostream>
#include <string>
using namespace std;

struct Medicine{
    int key = 0, quantity = 0;
    string name;
    bool occupied = false;
};
// Nine slots; hash(key) = key mod 9. Both replacement variants are available.
class HashTable{
    Medicine table[9];
    bool replacement;
    int hash(int key){ return (key % 9 + 9) % 9; }
public:
    HashTable(bool mode): replacement(mode){}
    int search(int key){
        int home = hash(key);
        for(int step = 0; step < 9; step++){
            int i = (home + step) % 9;
            if(!table[i].occupied) return -1;
            if(table[i].key == key) return i;
        }
        return -1;
    }
    void insert(Medicine item){
        int existing = search(item.key);
        if(existing != -1){ table[existing] = item; cout << "Stock updated.\n"; return; }
        int home = hash(item.key), free = -1;
        for(int step = 0; step < 9; step++){
            int i = (home + step) % 9;
            if(!table[i].occupied){ free = i; break; }
        }
        if(free == -1){ cout << "Hash table full.\n"; return; }
        // With replacement: put a new home key in its home slot and move the
        // foreign occupant to the first free slot along the probe sequence.
        if(replacement && table[home].occupied && hash(table[home].key) != home){
            table[free] = table[home];
            table[home] = item;
        }
        else table[free] = item;
        cout << "Stock stored.\n";
    }
    void show(int index){
        cout << index << "\t" << table[index].key << "\t" << table[index].name
             << "\t" << table[index].quantity << "\n";
    }
    void find(int key){
        int index = search(key);
        if(index == -1) cout << "Medicine not found.\n";
        else show(index);
    }
    void display(){
        cout << "Index\tKey\tMedicine\tQuantity\n";
        for(int i = 0; i < 9; i++){
            if(table[i].occupied) show(i);
            else cout << i << "\tEMPTY\n";
        }
    }
};
int main(){
    int mode;
    cout << "Probing mode: 1. Without replacement  2. With replacement\nEnter mode: ";
    if(!(cin >> mode) || (mode != 1 && mode != 2)) return 0;
    HashTable stock(mode == 2);
    int choice, key;
    while(true){
        cout << "\n===== Medical Stock Menu =====\n1. Insert / update\n2. Search\n3. Display\n4. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 4) break;
        switch(choice){
            case 1: {
                Medicine item;
                cout << "Enter non-negative medicine key: ";
                if(!(cin >> item.key)) return 0;
                if(item.key < 0){ cout << "Invalid key.\n"; break; }
                cout << "Enter medicine name: ";
                if(!getline(cin >> ws, item.name)) return 0;
                cout << "Enter stock quantity: ";
                if(!(cin >> item.quantity)) return 0;
                if(item.quantity < 0){ cout << "Invalid quantity.\n"; break; }
                item.occupied = true;
                stock.insert(item); break;
            }
            case 2:
                cout << "Enter medicine key: "; if(!(cin >> key)) return 0;
                stock.find(key); break;
            case 3: stock.display(); break;
            default: cout << "Invalid choice.\n";
        }
    }
}
