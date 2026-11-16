#include <iostream>
#include <cmath>
using namespace std;

// Adapted from PL/linked/polynomial.cpp using a singly linked list.
class Node {
public:
    double coefficient;
    int exponent;
    Node* next;

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

    Polynomial() {
        head = nullptr;
        tail = nullptr;
    }

    ~Polynomial() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Same append-at-tail pattern as addTerm() in the original polynomial code.
    void addTerm(double coefficient, int exponent) {
        Node* newNode = new Node(coefficient, exponent);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Find the matching exponent in the result before adding a new term.
    void addToResult(Polynomial& result, double coefficient, int exponent) {
        Node* current = result.head;
        while (current != nullptr && current->exponent != exponent) {
            current = current->next;
        }
        if (current != nullptr) {
            current->coefficient += coefficient;
        } else {
            result.addTerm(coefficient, exponent);
        }
    }

    void add(Polynomial& other, Polynomial& result) {
        // Copy both inputs into the result, combining matching exponents.
        for (Node* current = head; current != nullptr; current = current->next) {
            addToResult(result, current->coefficient, current->exponent);
        }
        for (Node* current = other.head; current != nullptr; current = current->next) {
            addToResult(result, current->coefficient, current->exponent);
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
            addTerm(coefficient, exponent);
        }
        return true;
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
    return 0;
}
