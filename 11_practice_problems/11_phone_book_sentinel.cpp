#include <iostream>
#include <string>
using namespace std;

// How this program works:
// Keep friend records in alphabetical order by name.
// Sentinel search places the wanted name in one extra slot at the end.
// The search always stops; stopping at the extra slot means not found.
// If missing, shift larger names right and insert the new friend.

struct Friend{
    string name, mobile; // String preserves leading zeros and country codes.
};
class PhoneBook{
    Friend records[101]; // 100 records plus one reserved sentinel slot.
    int count = 0;
public:
    int search(string name){
        // This extra entry is temporary; it is not a real friend record.
        records[count].name = name;
        int i = 0;
        // Sentinel guarantees a match, so the loop needs no boundary check.
        while(records[i].name != name) i++;
        // An index below count is a real match; count itself is the sentinel.
        if(i < count) return i;
        return -1;
    }
    void findOrInsert(string name){
        int index = search(name);
        if(index != -1){ cout << records[index].name << ": " << records[index].mobile << "\n"; return; }
        if(count == 100){ cout << "Phone book full.\n"; return; }
        string mobile;
        cout << "Friend not present. Enter mobile number to insert: ";
        if(!(cin >> mobile)) return;
        int i = count - 1;
        // Insert directly in alphabetical (case-sensitive) order.
        while(i >= 0 && records[i].name > name){ records[i + 1] = records[i]; i--; }
        records[i + 1] = {name, mobile}; count++;
        cout << "Friend inserted.\n";
    }
    void display(){
        if(count == 0) cout << "Phone book empty.\n";
        for(int i = 0; i < count; i++) cout << records[i].name << "\t" << records[i].mobile << "\n";
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    PhoneBook book; int choice; string name;
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Phone Book Menu =====\n1. Search / insert friend\n2. Display sorted phone book\n3. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 3) break;
        switch(choice){
            case 1:
                cout << "Enter full name: ";
                if(!getline(cin >> ws, name)) return 0;
                book.findOrInsert(name); break;
            case 2: book.display(); break;
            default: cout << "Invalid choice.\n";
        }
    }
}
