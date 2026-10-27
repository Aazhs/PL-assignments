 #include <iostream>
#include <iomanip>
#include <limits>
 #include <string>

using namespace std;

 class Node {
 public:
	 string type;
	 double price;
	 Node* next;

	 Node(string t, double p);
 };

 class Queue {
 public:
	 // Only tail is kept: tail->next is the front of the queue, because the list is circular
	 Node* tail;
	 int capacity;
	 int size;

	 explicit Queue(int maxOrders);
	 ~Queue();
	 void add();
	 void serve(bool showMessage = true);
	 void show();
	 bool isFull() const;
	 bool isEmpty() const;
 };

 Node::Node(string t, double p) {
	 type = t;
	 price = p;
	 next = nullptr;
 }

 Queue::Queue(int maxOrders) {
	 tail = nullptr;
	 capacity = maxOrders;
	 size = 0;
 }

 Queue::~Queue() {
	 // Serve every remaining order without printing to free all the nodes
	 while (!isEmpty()) {
		 serve(false);
	 }
 }

 bool Queue::isFull() const {
	 return size == capacity;
 }

 bool Queue::isEmpty() const {
	 return size == 0;
 }

 void Queue::add() {
	 if (isFull()) {
		 cout << "The parlor is full. Maximum orders: " << capacity << ".\n";
		 return;
	 }

	 string t;
	 double p;

	 cout << "Enter pizza type: ";
	 // Bad input: clear the error state and throw away the rest of the line
	 if (!(cin >> t)) {
		 cin.clear();
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 cout << "Invalid pizza type. Order was not placed.\n";
		 return;
	 }
	 cout << "Enter cost: ";
	 if (!(cin >> p) || p < 0) {
		 cin.clear();
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 cout << "Cost must be a non-negative number. Order was not placed.\n";
		 return;
	 }

	 Node* n = new Node(t, p);

	 if (isEmpty()) {
		 // First node points to itself to make the circle
		 tail = n;
		 tail->next = tail;
	 }
	 else {
		 // Add the node after tail, keep the circle closed, then make it the new tail
		 n->next = tail->next;
		 tail->next = n;
		 tail = n;
	 }
	 ++size;

	 cout << "Pizza placed successfully (" << size << '/' << capacity
		  << " orders).\n";
 }

 void Queue::serve(bool showMessage) {
	 if (isEmpty()) {
		 cout << "No pizza is waiting to be served.\n";
		 return;
	 }

	 // The front of the queue is the node after tail
	 Node* n = tail->next;

	 // Only one node was left, so the queue is now empty
	 if (n == tail) {
		 tail = nullptr;
	 }
	 else {
		 // Skip the front node so tail now points to the new front
		 tail->next = n->next;
	 }
	 --size;

	 if (showMessage) {
		 cout << "Served pizza: " << n->type
			   << " | Cost: $" << fixed << setprecision(2) << n->price
			   << "\n";
	 }

	 delete n;
 }

 void Queue::show() {
	 if (isEmpty()) {
		 cout << "No pizzas are waiting.\n";
		 return;
	 }

	 Node* p = tail->next;
	 cout << "\nPizzas waiting to be served (" << size << '/' << capacity
		  << "):\n";

	 // do-while so the first node is printed before the loop condition (p back at front) is checked
	 do {
		 cout << "Pizza type: " << p->type
			   << " | Cost: $" << fixed << setprecision(2) << p->price << "\n";
		 p = p->next;
	 } while (p != tail->next);
 }

 int main() {
	 int maxOrders;
	 cout << "Enter the maximum number of orders (M): ";
	 while (!(cin >> maxOrders) || maxOrders <= 0) {
		 cin.clear();
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 cout << "M must be a positive integer. Try again: ";
	 }

	 Queue q(maxOrders);
	 int choice;

	 while (true) {
		 cout << "\n========== PIZZA MENU ==========\n";
		 cout << "1. Place pizza\n";
		 cout << "2. Serve pizza\n";
		 cout << "3. Display waiting pizzas\n";
		 cout << "4. Exit\n";
		 cout << "Enter your choice: ";
		  if (!(cin >> choice)) {
			  cin.clear();
			  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			  cout << "Please enter a menu number from 1 to 4.\n";
			  continue;
		  }

		 switch (choice) {
			 case 1:
				 q.add();
				 break;
			 case 2:
				 q.serve();
				 break;
			 case 3:
				 q.show();
				 break;
			 case 4:
				 cout << "Exiting pizza menu.\n";
				 return 0;
			 default:
				 cout << "Invalid choice. Try again.\n";
		 }
	 }
 }
