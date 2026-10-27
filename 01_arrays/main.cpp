#include <iostream>
#include "aasharuser.cpp"

using namespace std;

int main() {
	AadharUser records[100];
	int count = 0;
	int choice;

	do {
		cout << "\n===== Aadhar Menu =====\n";
		cout << "1 - input aadhar person\n";
		cout << "2 - update details of aadhar\n";
		cout << "3 - add aadhar person at specific index\n";
		cout << "4 - remove aadhar person\n";
		cout << "5 - find aadhar by aadhar number\n";
		cout << "6 - view all records\n";
		cout << "7 - exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
            cout << "Enter details for record " << count + 1 << ":\n";
            records[count].inputAadhar();
            count++;
			break;
		case 2:
			if (count == 0) {
				cout << "No records to update.\n";
			} else {
				int index;
				cout << "Enter record index to update (1 to " << count << "): ";
				cin >> index;
				if (index < 1 || index > count) {
					cout << "Invalid index.\n";
				} else {
					cout << "Enter new details:\n";
					records[index - 1].inputAadhar();
				}
			}
			break;
			case 3: {
            int index;
            cout << "Enter position to insert (1 to " << count + 1 << "): ";
            cin >> index;
            if (index < 1 || index > count + 1) {
                cout << "Invalid position.\n";
            } else {
                // Shift records one step right (starting from the end) to free up the slot at index-1
                for (int i = count; i >= index; --i) {
                    records[i] = records[i - 1];
                }

                cout << "Enter details for new record:\n";
                records[index - 1].inputAadhar();
                count++;
            }
			break;
			}
			case 4: {
			if (count == 0) {
				cout << "No records to remove.\n";
			} else {
				int index;
				cout << "Enter record index to remove (1 to " << count << "): ";
				cin >> index;
				if (index < 1 || index > count) {
					cout << "Invalid index.\n";
				} else {
					// Shift every record after the removed one a step left to fill the gap
					for (int i = index - 1; i < count - 1; ++i) {
						records[i] = records[i + 1];
					}
					count--;
					cout << "Record removed.\n";
				}
			}
			break;
			}
			case 5: {
				if (count == 0) {
					cout << "No records available.\n";
				} else {
					int searchNumber;
					bool found = false;
					cout << "Enter Aadhar number to search: ";
					cin >> searchNumber;

					for (int i = 0; i < count; ++i) {
						if (records[i].aadharNumber == searchNumber) {
							cout << "\nRecord found at index " << i + 1 << '\n';
							records[i].viewAadhar();
							found = true;
							break;
						}
					}

					if (!found) {
						cout << "No record found with that Aadhar number.\n";
					}
				}
				break;
			}
			case 6:
			if (count == 0) {
				cout << "No records available.\n";
			} else {
				for (int i = 0; i < count; ++i) {
					cout << "\nRecord " << i + 1 << '\n';
					records[i].viewAadhar();
				}
			}
			break;
			case 7:
			cout << "Exiting program.\n";
			break;
		default:
			cout << "Invalid choice.\n";
			break;
		}
	} while (choice != 7);

	return 0;
}
