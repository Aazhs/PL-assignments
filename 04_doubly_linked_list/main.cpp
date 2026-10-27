#include <iostream>
using namespace std;

class Node{
public:
    Node *next;
    int data;
    Node *prev;

    Node(){
        prev = nullptr;
        data = 0;
        next = nullptr;
    }
};

class Dll{
public:
    Node *head;

    Dll(){
        head = nullptr;
    }

    void create(){
        cout<<"Enter value to add:- ";
        int val;cin>>val;

        Node* temp = new Node();
        temp->data = val;

        if(head == nullptr){
            head = temp;
        }
        else{
            Node *p = head;
            // Go to the last node, then link the new node after it in both directions
            while(p != nullptr && p->next != nullptr){
                p = p->next;
            }
            p->next = temp;
            temp->prev = p;
        }
    }

    void createNValues(int n){
        cout << "Enter " << n << " values: ";
        for(int i = 0; i < n; i++){
            int val;
            cin >> val;

            Node* temp = new Node();
            temp->data = val;

            if(head == nullptr){
                head = temp;
            }
            else{
                Node *p = head;
                // Go to the last node, then link the new node after it in both directions
                while(p != nullptr && p->next != nullptr){
                    p = p->next;
                }
                p->next = temp;
                temp->prev = p;
            }
        }
    }

    void display(){
        Node* temp = head;
        while(temp != nullptr){
            cout<<temp->data<<" - ";
            temp = temp->next;
        }
        cout<<"NULL\n";
    }

    void display_rev(){
        Node* p = head;
        // Go to the last node first, then walk backwards using prev
        while(p != nullptr && p->next != nullptr){
            p = p->next;
        }

        while(p != nullptr){
            cout<<p->data<<" - ";
            p = p->prev;
        }

        cout<<"NULL\n";
    }

    int getSize(){
        int size = 0;
        Node* temp = head;
        while(temp != nullptr){
            size++;
            temp = temp->next;
        }

        return size;
    }

    // Bubble sort that swaps the nodes themselves (not just the data).
    // Keeps making passes until a full pass makes no swap.
    void sort(){
        Node *p;
        Node *ptr1, *ptr2, *temp;
        bool swapped = true;

        while(swapped){
            swapped = false;
            p = head;

            while(p->next != nullptr){
                if(p->data > p->next->data){
                    swapped = true;
                    ptr1 = p;
                    ptr2 = ptr1->next;
                    temp = ptr2->next;

                    // Point the node before ptr1 (or head) to ptr2
                    if(ptr1->prev == nullptr){
                        head = ptr2;
                    }
                    else{
                        ptr1->prev->next = ptr2;
                    }

                    // Rewire the pair so the order becomes: ... -> ptr2 -> ptr1 -> temp
                    ptr2->next = ptr1;
                    ptr2->prev = ptr1->prev;
                    ptr1->prev = ptr2;
                    ptr1->next = temp;

                    // Fix the back link of the node after the swapped pair
                    if(temp != nullptr){
                        temp->prev = ptr1;
                    }

                    // ptr1 is now one step ahead, so set p to ptr2; p = p->next below then lands on ptr1
                    p = ptr2;
                }

                p = p->next;
            }
        }
    }

    // Merges two sorted lists into this one by relinking their nodes (no new nodes are made).
    // r always points to the last node added to the merged list.
    void merge(Dll &l1, Dll &l2){
        Node *p = l1.head;
        Node *q = l2.head;
        Node *r = nullptr;

        head = nullptr;

        while(p != nullptr && q != nullptr){
            Node *selected;
            if(p->data <= q->data){
                selected = p;
                p = p->next;
            }
            else{
                selected = q;
                q = q->next;
            }

            selected->prev = r;

            if(r == nullptr){
                head = selected;
            }
            else{
                r->next = selected;
            }

            r = selected;
        }

        // One list is finished; attach the rest of the other list
        Node *remaining = p != nullptr ? p : q;
        while(remaining != nullptr){
            remaining->prev = r;

            if(r == nullptr){
                head = remaining;
            }
            else{
                r->next = remaining;
            }

            r = remaining;
            remaining = remaining->next;
        }

        if(r != nullptr){
            r->next = nullptr;
        }

        // The nodes now belong to the merged list, so the old lists must not use them
        l1.head = nullptr;
        l2.head = nullptr;
    }

};

int main(){
    Dll list1, list2, mergedList;
    int choice;

    while(true){
        cout << "\n--- Doubly Linked List Menu ---\n";
        cout << "1. Insert N values into List 1\n";
        cout << "2. Insert N values into List 2\n";
        cout << "3. Display List 1\n";
        cout << "4. Display List 2\n";
        cout << "5. Display List 1 in reverse\n";
        cout << "6. Display List 2 in reverse\n";
        cout << "7. Sort List 1\n";
        cout << "8. Sort List 2\n";
        cout << "9. Merge List 1 and List 2\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1: {
                int n;
                cout << "Enter number of values for List 1: ";
                cin >> n;
                list1.createNValues(n);
                break;
            }
            case 2: {
                int n;
                cout << "Enter number of values for List 2: ";
                cin >> n;
                list2.createNValues(n);
                break;
            }
            case 3:
                cout << "List 1: ";
                list1.display();
                break;
            case 4:
                cout << "List 2: ";
                list2.display();
                break;
            case 5:
                cout << "List 1 in reverse: ";
                list1.display_rev();
                break;
            case 6:
                cout << "List 2 in reverse: ";
                list2.display_rev();
                break;
            case 7:
                list1.sort();
                cout << "List 1 sorted.\n";
                break;
            case 8:
                list2.sort();
                cout << "List 2 sorted.\n";
                break;
            case 9: {
                mergedList.merge(list1, list2);
                cout << "Merged list: ";
                mergedList.display();
                break;
            }
            case 10:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}