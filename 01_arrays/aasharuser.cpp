#include <iostream>

using namespace std;

// One Aadhar record. main.cpp keeps an array of these objects
// and does insert / update / delete / search on that array.
class AadharUser {
public:
	int aadharNumber;
	char name[50];
	char dob[20];
	char address[100];

	// Read all details of this person from the keyboard
	void inputAadhar() {
		cout << "Enter Aadhar number: ";
		cin >> aadharNumber;
		// Drop the leftover newline from cin >> so the next getline doesn't read an empty line
		cin.ignore();

		cout << "Enter name: ";
		cin.getline(name, 50);  // getline reads the full line, so names with spaces work

		cout << "Enter date of birth: ";
		cin.getline(dob, 20);

		cout << "Enter address: ";
		cin.getline(address, 100);
	}

	// Print all details of this person
	void viewAadhar() const {
		cout << "Aadhar Number: " << aadharNumber << '\n';
		cout << "Name: " << name << '\n';
		cout << "Date of Birth: " << dob << '\n';
		cout << "Address: " << address << '\n';
	}
};