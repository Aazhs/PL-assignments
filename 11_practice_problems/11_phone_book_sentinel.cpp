#include <iostream>
#include <string>
using namespace std;

struct Friend
{
    string name, mobile; // A string keeps leading zeros in phone numbers.
};

int sentinelSearch(Friend book[], int count, string name)
{
    // The extra slot guarantees a match, so no boundary check is needed inside.
    book[count].name = name;
    int i = 0;
    while (book[i].name != name) i++;
    if (i < count) return i; // A real record matched.
    return -1; // Only the sentinel matched: friend is missing.
}

void insert(Friend book[], int& count, Friend person)
{
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

void display(Friend book[], int count)
{
    for (int i = 0; i < count; i++)
        cout << book[i].name << "\t" << book[i].mobile << endl;
}

int main()
{
    Friend book[101], person; // 100 friends and one sentinel slot.
    int n, count = 0;
    cout << "Enter number of friends (0 to 100): ";
    if (!(cin >> n) || n < 0 || n > 100) return 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter name: ";
        if (!getline(cin >> ws, person.name)) return 0;
        cout << "Enter mobile number: ";
        if (!(cin >> person.mobile)) return 0;
        if (sentinelSearch(book, count, person.name) == -1)
            insert(book, count, person);
        else cout << "Name already present.\n";
    }
    cout << "Sorted phone book:\n";
    display(book, count);

    cout << "Enter friend name to search: ";
    string name;
    if (!getline(cin >> ws, name)) return 0;
    int index = sentinelSearch(book, count, name);
    if (index != -1)
        cout << book[index].name << ": " << book[index].mobile << endl;
    else if (count == 100)
        cout << "Friend not found; phone book full.\n";
    else
    {
        person.name = name;
        cout << "Friend not found. Enter mobile number to insert: ";
        if (!(cin >> person.mobile)) return 0;
        insert(book, count, person);
        cout << "Updated phone book:\n";
        display(book, count);
    }
    return 0;
}
