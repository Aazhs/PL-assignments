#include <iostream>
#include <cmath>
using namespace std;

// One term, such as 5x^2, stores coefficient 5 and exponent 2.
struct Node
{
    double coefficient;
    int exponent;
    Node* next;
};

void insert(Node*& head, double coefficient, int exponent)
{
    // head is passed by reference because inserting first may change it.
    Node* current = head;
    Node* previous = nullptr;

    // Keep terms in descending order of exponent.
    while (current != nullptr && current->exponent > exponent)
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr && current->exponent == exponent)
    {
        // Same power: add the coefficients instead of making another node.
        current->coefficient += coefficient;
    }
    else
    {
        Node* temp = new Node{coefficient, exponent, current};
        if (previous == nullptr) head = temp;
        else previous->next = temp;
    }
}

bool input(Node*& head)
{
    int n, exponent;
    double coefficient;
    cout << "Enter number of terms: ";
    if (!(cin >> n) || n < 0) return false;
    cout << "Enter coefficient and exponent for each term:\n";
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> coefficient >> exponent) || exponent < 0) return false;
        insert(head, coefficient, exponent);
    }
    return true;
}

void add(Node* first, Node* second, Node*& result)
{
    // Insert every term into the result; insert() combines equal powers.
    while (first != nullptr)
    {
        insert(result, first->coefficient, first->exponent);
        first = first->next;
    }
    while (second != nullptr)
    {
        insert(result, second->coefficient, second->exponent);
        second = second->next;
    }
}

void display(Node* head)
{
    bool first = true;
    while (head != nullptr)
    {
        // Terms that cancel to zero should not appear in the answer.
        if (head->coefficient != 0)
        {
            if (!first)
            {
                if (head->coefficient < 0) cout << " - ";
                else cout << " + ";
            }
            else if (head->coefficient < 0) cout << "-";
            cout << abs(head->coefficient);
            if (head->exponent != 0) cout << "x^" << head->exponent;
            first = false;
        }
        head = head->next;
    }
    if (first) cout << "0";
    cout << endl;
}

void clear(Node* head)
{
    // Save the next address before deleting the current node.
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Node* first = nullptr;
    Node* second = nullptr;
    Node* result = nullptr;
    cout << "First polynomial:\n";
    bool valid = input(first);
    if (valid)
    {
        cout << "Second polynomial:\n";
        valid = input(second);
    }
    if (valid)
    {
        add(first, second, result);
        cout << "Sum: ";
        display(result);
    }
    clear(first);
    clear(second);
    clear(result);
    return 0;
}
