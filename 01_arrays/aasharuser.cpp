#include <iostream>

using namespace std;

class AadharUser {
public:
	int aadharNumber;
	char name[50];
	char dob[20];
	char address[100];

	void inputAadhar() {
		cout << "Enter Aadhar number: ";
		cin >> aadharNumber;
		// Drop the leftover newline from cin >> so the next getline doesn't read an empty line
		cin.ignore();

		cout << "Enter name: ";
		cin.getline(name, 50);

		cout << "Enter date of birth: ";
		cin.getline(dob, 20);

		cout << "Enter address: ";
		cin.getline(address, 100);
	}

	void viewAadhar() const {
		cout << "Aadhar Number: " << aadharNumber << '\n';
		cout << "Name: " << name << '\n';
		cout << "Date of Birth: " << dob << '\n';
		cout << "Address: " << address << '\n';
	}
};