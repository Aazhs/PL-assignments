#include <iostream>
#include <string>
using namespace std;

class Friend
{
public:
    string name, mobile; // A string keeps leading zeros in phone numbers.
};

// Uses the shift-right loop from insertionSortByName() in PL/assignment10_class.cpp.
// Sentinel search is added for this phone-book problem.
class PhoneBook
{
public:
    Friend book[101]; // 100 friends and one sentinel slot.
    int count;

    PhoneBook() {
        count = 0;
    }

    int sentinelSearch(string name)
    {
        // The extra slot guarantees a match, so no boundary check is needed inside.
        book[count].name = name;
        int i = 0;
        while (book[i].name != name) i++;
        if (i < count) return i; // A real record matched.
        return -1; // Only the sentinel matched: friend is missing.
    }

    void insertByName(Friend person)
    {
        if (count == 100) return; // Reserve the extra slot for the sentinel.
        int i = count - 1;
        // Make space by moving alphabetically larger names one place right.
        while (i >= 0 && book[i].name > person.name)
        {
            book[i + 1] = book[i];
            i--;
        }
        book[i + 1] = person;
        count++;
    }

    void display()
    {
        for (int i = 0; i < count; i++)
            cout << book[i].name << "\t" << book[i].mobile << endl;
    }
};

int main()
{
    PhoneBook contacts;
    Friend person;
    int n;
    cout << "Enter number of friends (0 to 100): ";
    if (!(cin >> n) || n < 0 || n > 100) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter name: ";
        if (!getline(cin >> ws, person.name)) return 0;
        cout << "Enter mobile number: ";
        if (!(cin >> person.mobile)) return 0;
        if (contacts.sentinelSearch( person.name) == -1)
            contacts.insertByName( person);
        else cout << "Name already present.\n";
    }
    cout << "Sorted phone book:\n";
    contacts.display();

    cout << "Enter friend name to search: ";
    string name;
    if (!getline(cin >> ws, name)) return 0;
    int index = contacts.sentinelSearch( name);
    if (index != -1)
        cout << contacts.book[index].name << ": " << contacts.book[index].mobile << endl;
    else if (contacts.count == 100)
        cout << "Friend not found; phone book full.\n";
    else
    {
        person.name = name;
        cout << "Friend not found. Enter mobile number to insert: ";
        if (!(cin >> person.mobile)) return 0;
        contacts.insertByName( person);
        cout << "Updated phone book:\n";
        contacts.display();
    }
    return 0;
}
