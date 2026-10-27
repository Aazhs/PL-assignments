#include <iostream>

using namespace std;

class Node {
	public:
		int data;
		Node* next;

		Node(int val) {
			data = val;
			next = nullptr;
		}
};

class LinkedList {
	public:
		Node* head;
		int size;
		LinkedList() {
			head = nullptr;
			size = 0;
		}

		~LinkedList() {
			while (head != nullptr) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
		}

		void insertAtBeginning(int val) {
			Node* newNode = new Node(val);
			newNode->next = head;
			head = newNode;
			size++;
			cout << "Inserted " << val << " at the beginning.\n";
		}

		void insertAtEnd(int val) {
			Node* newNode = new Node(val);

			if (head == nullptr) {
				head = newNode;
				size++;
				cout << "Inserted " << val << " at the end (as head).\n";
				return;
			}

			Node* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}

			temp->next = newNode;
			size++;
			cout << "Inserted " << val << " at the end.\n";
		}

		void display() {
			if (head == nullptr) {
				cout << "The linked list is empty.\n";
				return;
			}

			Node* temp = head;
			cout << "Linked List: ";
			while (temp != nullptr) {
				cout << temp->data << " -> ";
				temp = temp->next;
			}
			cout << "nullptr\n";
		}

		void insert_by_pos(int val, int pos){
			if (pos < 1) {
				cout << "Position must be 1 or greater.\n";
				return;
			}

			if (pos == 1) {
				insertAtBeginning(val);
				return;
			}

			Node* p = head;
			// Walk to the node just before the given position
			for (int i = 1; p != nullptr && i < pos - 1; i++) {
				p = p->next;
			}

			if (p == nullptr) {
				cout << "Position is outside the linked list.\n";
				return;
			}

			// Link in the new node: new -> p's old next, then p -> new
			Node* temp = new Node(val);
			temp->next = p->next;
			p->next = temp;
			size++;
			cout << "Added " << val << " at position " << pos << ".\n";
		}
		void insert_by_val(int val , int search){
			Node* p = head;
			while (p != nullptr && p->data != search) {
				p = p->next;
			}

			if (p == nullptr) {
				cout << "Value " << search << " was not found.\n";
				return;
			}

			Node* temp = new Node(val);
			temp->next = p->next;
			p->next = temp;
			size++;
			cout << "Added " << val << " after value " << search << ".\n";

		}
		void delete_first(){
			if (head == nullptr) {
				cout << "The linked list is already empty.\n";
				return;
			}
			Node* temp = head;
			head = head->next;
			delete(temp);
			size--;
			cout << "First element deleted.\n";
		}

		void delete_last(){
			if (head == nullptr) {
				cout << "The linked list is already empty.\n";
				return;
			}

			if (head->next == nullptr) {
				delete head;
				head = nullptr;
				size--;
				cout << "Last element deleted.\n";
				return;
			}

			Node* temp = head;
			// Stop at the second last node so we can cut off the last one
			while (temp->next->next != nullptr){
				temp = temp->next;
			}
			delete temp->next;
			temp->next = nullptr;
			size--;
			cout << "Last element deleted.\n";
		}

		void delete_by_pos(int pos){
			if (pos < 1 || pos > size) {
				cout << "Position is outside the linked list.\n";
				return;
			}

			if (pos == 1) {
				// Delete the head
				Node* temp = head;
				head = head->next;
				delete temp;
				size--;
				cout << "Element at position " << pos << " deleted.\n";
				return;
			}

			// For positions > 1
			Node* temp = head;
			// Move to the node just before the one being deleted
			for (int i = 1; i < pos - 1; i++) {
				temp = temp->next;
			}

			Node* nodeToDelete = temp->next;
			// Skip over the node in the chain, then free it
			temp->next = nodeToDelete->next;
			delete nodeToDelete;
			size--;
			cout << "Element at position " << pos << " deleted.\n";
		}


		int getSize() {
			return size;
		}

		void displaySize() {
			cout << "Current size of linked list: " << size << " element(s)\n";
		}

		void bubbleSort() {
			if (head == nullptr || head->next == nullptr) {
				cout << "Linked list is empty or has only one element. Already sorted.\n";
				return;
			}

			// After every pass the biggest remaining value reaches the end, so each pass
			// checks one pair less. Only the data is swapped, the links stay the same.
			for (int i = 0; i < size - 1; i++) {
				Node* current = head;
				Node* nextNode = current->next;

				for (int j = 0; j < size - i - 1; j++) {
					if (current->data > nextNode->data) {
						// Swap data between nodes
						int temp = current->data;
						current->data = nextNode->data;
						nextNode->data = temp;
					}
					current = nextNode;
					nextNode = nextNode->next;
				}
			}
			cout << "Linked list sorted in ascending order.\n";
		}

		void search(int val){
			Node *temp = head;
			int flag = 0;
			while (temp->next->data != val){
				temp = temp->next;
				flag = 1;
			}

			if(flag == 0) cout<<"element not found\n";
			else cout<<"Element is found\n";
		}
	};

int main() {
	LinkedList list;
	int choice;

	cout << "\n========== LINKED LIST MENU ==========" << endl;
	cout << "1. Insert at beginning\n"
		 << "2. Insert at end\n"
		 << "3. Insert at position\n"
		 << "4. Insert after a value\n"
		 << "5. Delete first element\n"
		 << "6. Delete last element\n"
		 << "7. Delete at position\n"
		 << "8. Search element\n"
		 << "9. Display linked list\n"
		 << "10. Bubble sort\n"
		 << "0. Exit\n";

	do {
		cout << "\n---------------------------------------\n";
		cout << "Enter your choice: ";
		if (!(cin >> choice)) {
			cout << "Invalid input. Please enter a number.\n";
			return 1;
		}

		switch (choice) {
			case 1: {
				int value;
				cout << "Enter value: ";
				cin >> value;
				list.insertAtBeginning(value);
				list.display();
				break;
			}
			case 2: {
				int value;
				cout << "Enter value: ";
				cin >> value;
				list.insertAtEnd(value);
				list.display();
				break;
			}
			case 3: {
				int value, position;
				cout << "Enter value: ";
				cin >> value;
				cout << "Enter position: ";
				cin >> position;
				list.insert_by_pos(value, position);
				list.display();
				break;
			}
			case 4: {
				int value, searchValue;
				cout << "Enter value to insert: ";
				cin >> value;
				cout << "Insert after which value: ";
				cin >> searchValue;
				list.insert_by_val(value, searchValue);
				list.display();
				break;
			}
			case 5:
				list.delete_first();
				list.display();
				break;
			case 6:
				list.delete_last();
				list.display();
				break;
			case 7: {
				int position;
				cout << "Enter position to delete: " << "1-"<<list.getSize()<<endl;
				cin >> position;
				list.delete_by_pos(position);
				list.display();
				break;
			}
			case 8: {
				list.displaySize();
				int value;
				cout << "Enter value to search: ";
				cin >> value;
				list.search(value);
				list.display();
				break;
			}
			case 9:
				list.display();
				break;
			case 10:
				list.bubbleSort();
				list.display();
				break;
			case 0:
				cout << "Goodbye!\n";
				break;
			default:
				cout << "Invalid choice. Please choose from 0 to 10.\n";
		}
	} while (choice != 0);

	return 0;
}
