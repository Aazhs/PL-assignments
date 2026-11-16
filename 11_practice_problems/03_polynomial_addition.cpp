#include <iostream>
#include <cmath>
using namespace std;

// One term, such as 5x^2, stores coefficient 5 and exponent 2.
class Node
{
public:
    double coefficient;
    int exponent;
    Node* next;
};

// Keep the data and its operations together in one simple class.
class Polynomial
{
public:
    Node* head = nullptr;

    void insert(double coefficient, int exponent)
    {
        // head belongs to this polynomial; inserting first may change it.
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

    bool input()
    {
        int n, exponent;
        double coefficient;
        cout << "Enter number of terms: ";
        if (!(cin >> n) || n < 0) return false;
        cout << "Enter coefficient and exponent for each term:\n";
        for (int i = 0; i < n; i++)
        {
            if (!(cin >> coefficient >> exponent) || exponent < 0) return false;
            insert(coefficient, exponent);
        }
        return true;
    }

    void add(Polynomial& other, Polynomial& result)
    {
        Node* first = head;
        Node* second = other.head;
        // Insert every term into the result; insert() combines equal powers.
        while (first != nullptr)
        {
            result.insert(first->coefficient, first->exponent);
            first = first->next;
        }
        while (second != nullptr)
        {
            result.insert(second->coefficient, second->exponent);
            second = second->next;
        }
    }

    void display()
    {
        Node* current = head;
        bool first = true;
        while (current != nullptr)
        {
            // Terms that cancel to zero should not appear in the answer.
            if (current->coefficient != 0)
            {
                if (!first)
                {
                    if (current->coefficient < 0) cout << " - ";
                    else cout << " + ";
                }
                else if (current->coefficient < 0) cout << "-";
                cout << abs(current->coefficient);
                if (current->exponent != 0) cout << "x^" << current->exponent;
                first = false;
            }
            current = current->next;
        }
        if (first) cout << "0";
        cout << endl;
    }

    void clear()
    {
        // Save the next address before deleting the current node.
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main()
{
    Polynomial first, second, result;
    cout << "First polynomial:\n";
    bool valid = first.input();
    if (valid)
    {
        cout << "Second polynomial:\n";
        valid = second.input();
    }
    if (valid)
    {
        first.add(second, result);
        cout << "Sum: ";
        result.display();
    }
    first.clear();
    second.clear();
    result.clear();
    return 0;
}
