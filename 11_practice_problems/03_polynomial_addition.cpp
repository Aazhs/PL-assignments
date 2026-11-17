/*
PRACTICE PROBLEM 3: POLYNOMIAL ADDITION USING A LINKED LIST

PROBLEM:
Represent two polynomials as linked lists and find their sum.
A polynomial term has a coefficient and exponent, such as 5x^2.
Terms with equal exponents must be combined in the answer.

EXAMPLE:
(2x^2 + 3) + (5x^2 + 1x^1) = 7x^2 + 3 + 1x^1.
The answer keeps terms in the order their exponents first appear.

HOW TO SOLVE:
1. Store each input term in a Node with coefficient, exponent and next.
2. Append terms using addTerm(), with head and tail marking the ends.
3. Visit every term in both input lists.
4. For each term, addToResult() searches the result for its exponent.
5. If found, add the coefficients; otherwise append a new result term.
6. Display the result, skipping terms whose coefficients cancel to zero.

VARIABLES / IMPORTANT POINTS:
head points to the first term, tail to the last; nullptr means no node.
current walks along a list without changing its head.
The inputs stay unchanged because the result owns separate nodes.
An empty or fully cancelled polynomial prints 0. Destructors free the nodes.
*/

#include <iostream>
#include <cmath>
using namespace std;

// Adapted from PL/linked/polynomial.cpp using a singly linked list.
class Node {
public:
    double coefficient;
    int exponent;
    Node* next;

    // Create one term and end its link with nullptr until another term is attached.
    Node(double c, int e) {
        coefficient = c;
        exponent = e;
        next = nullptr;
    }
};

class Polynomial {
public:
    Node* head;
    Node* tail;

    // Start an empty list: neither the first nor last term exists yet.
    Polynomial() {
        head = nullptr;
        tail = nullptr;
    }

    // Release all owned nodes when this object leaves scope; save next before deleting.
    ~Polynomial() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Same append-at-tail pattern as addTerm() in the original polynomial code.
    // Append one input/result term in constant time using tail; handle the first node separately.
    void addTerm(double coefficient, int exponent) {
        Node* newNode = new Node(coefficient, exponent);
        // First node: head and tail must both point to this same new node.
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            // Non-empty list: attach after the old tail before moving tail forward.
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Find the matching exponent in the result before adding a new term.
    // Search the result for the exponent; combine its coefficient or append a new power.
    void addToResult(Polynomial& result, double coefficient, int exponent) {
        Node* current = result.head;
        // Stop at a matching power or the end; test nullptr before reading a node.
        while (current != nullptr && current->exponent != exponent) {
            current = current->next;
        }
        if (current != nullptr) {
            // For example, coefficients 2 and 5 at exponent 3 become coefficient 7.
            current->coefficient += coefficient;
        } else {
            result.addTerm(coefficient, exponent);
        }
    }

    // Read both original lists without modifying them and build a separate sum list.
    void add(Polynomial& other, Polynomial& result) {
        // Copy both inputs into the result, combining matching exponents.
        for (Node* current = head; current != nullptr; current = current->next) {
            addToResult(result, current->coefficient, current->exponent);
        }
        for (Node* current = other.head; current != nullptr; current = current->next) {
            addToResult(result, current->coefficient, current->exponent);
        }
    }

    // Read a term count followed by coefficient/exponent pairs; accept only non-negative powers.
    bool input()
    {

        int n, exponent;
        double coefficient;
        cout << "Enter number of terms: ";
        cin >> n;

        if (n < 0) return false;
        cout << "Enter coefficient and exponent for each term:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> coefficient >> exponent;

            if (exponent < 0) return false;
            addTerm(coefficient, exponent);
        }
        return true;
    }

    // Traverse with a local pointer, omit cancelled terms, and handle plus/minus signs correctly.
    void display()
    {
        Node* current = head;
        // Track whether anything has been printed so there is no leading plus sign.
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
        // If no non-zero term was printed, the whole polynomial is zero.
        if (first) cout << "0";
        cout << endl;
    }

};

// Build two polynomial objects and a fresh result; their destructors clean up at the end.
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
    return 0;
}
