/*
PRACTICE PROBLEM 11: SORTED PHONE BOOK WITH SENTINEL SEARCH

PROBLEM:
Store friends' names and mobile numbers in alphabetical name order.
Search using sentinel search. If a name is missing, insert it in sorted order.

EXAMPLE:
Enter Zoe then Amy -> phone book displays Amy, Zoe.
Search for Ben -> ask for his mobile number, then display Amy, Ben, Zoe.

HOW TO SOLVE:
1. Read the initial friends, inserting each at its alphabetical position.
2. Before searching, put the requested name in one extra sentinel slot.
3. Scan names until one matches; the sentinel guarantees the loop will stop.
4. If the matched index is below count, it is a real friend: show the number.
5. If it equals count, the friend is missing: ask for the mobile number.
6. Shift larger names right and insert the new friend if the book has space.

VARIABLES / IMPORTANT POINTS:
book has 101 slots: 100 real records and one reserved sentinel at book[count].
count does not include the sentinel, so display never shows the temporary name.
Mobile numbers are strings to preserve leading zeros. Names are case-sensitive.
Duplicate initial names are skipped; a full book can still be searched.
*/

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

    // Start with zero real friends; the extra array slot is reserved for search.
    PhoneBook() {
        count = 0;
    }

    // Put the wanted name just after the real entries so the scan always finds a match.
    int sentinelSearch(string name)
    {
        // The extra slot guarantees a match, so no boundary check is needed inside.
        // Overwrite only the unused sentinel slot, leaving every real friend record intact.
        book[count].name = name;
        int i = 0;
        while (book[i].name != name) i++;
        // A match before the sentinel is real; a match at count means the name was absent.
        if (i < count) return i; // A real record matched.
        return -1; // Only the sentinel matched: friend is missing.
    }

    // Make a sorted gap by shifting larger names right, then store the new friend there.
    void insertByName(Friend person)
    {
        if (count == 100) return; // Reserve the extra slot for the sentinel.
        // Start at the last real name; inserting at the front may shift every existing record.
        int i = count - 1;
        // Make space by moving alphabetically larger names one place right.
        while (i >= 0 && book[i].name > person.name)
        {
            book[i + 1] = book[i];
            i--;
        }
        // The gap is now at i+1, including index 0 if every earlier name was larger.
        book[i + 1] = person;
        count++;
    }

    // Print real records only: the sentinel at index count must never be shown.
    void display()
    {
        for (int i = 0; i < count; i++)
            cout << book[i].name << "\t" << book[i].mobile << endl;
    }
};

// Load unique friends, display their sorted names, then search and optionally insert one name.
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
    // Searching is allowed even when all 100 real slots are full because slot 100 is reserved.
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
