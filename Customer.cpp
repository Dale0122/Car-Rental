#include "Customer.h"
#include "Misc.h"
#include <iomanip>

void Customer_List::addNewCustomer() {
	string name, address;
	int index; bool found;

	while (true) {
		inputCustomerInfo(name, address);
		searchNames(name, index, found);
		if (!found)
			break;

		int choice;
		cout << setw(15) << "" << "ERROR. That name already exists in the customer database. \n\n";

		cout << setw(15) << "" << "Would you like to try again? \n";
		cout << setw(20) << "" << "[1] Yes \n";
		cout << setw(20) << "" << "[2] No \n";
		inputValidation(choice, 1, 2);

		if (choice == 2)
			return;
	}
	if (name == "" || address == "") {
		cout << setw(15) << "" << "Append failed: Information incomplete. \n";
		return;
	}

	int newId = customerCount+1;
	addToVectors(newId, name, address);

	cout << setw(15) << "" << "The following customer information has been successfully added to the database: \n\n";
	cout << setw(20) << "" << setw(20) << left << "Customer ID" <<
		setw(5) << setfill('0') << right << sortedIdVec[index].customerId << setfill(' ') << "\n";
	cout << setw(20) << "" << setw(20) << left << "Customer Name" <<
		sortedIdVec[index].customerName << "\n";
	cout << setw(20) << "" << setw(20) << left << "Customer Address" <<
		sortedIdVec[index].customerAddress << "\n";
	cout << endl;
}

void Customer_List::addToVectors(int code, string name, string address) {
	++customerCount;
	sortedIdVec.push_back(CustomerInfo(code, name, address));
	sortedNameVec.push_back(CustomerInfo(code, name, address));
}

void Customer_List::inputCustomerInfo(string &name, string &address) {
	cout << setw(15) << "" << "Please enter the following information for Customer ID #" << customerCount + 1 << "\n\n";

	cout << setw(20) << "" << setw(20) << left << "Customer Name";
	getline(cin, name);
	cout << setw(20) << "" << setw(20) << left << "Customer Address";
	getline(cin, address);

	cout << "\n";
}

void Customer_List::checkOneCustomer() {
	int id, index;
	bool found;
	cout << setw(15) << "" << setw(30) << left << "Enter customer ID";

	while (!(cin >> id)) {
		cout << setw(18) << "" << "ERROR. Please try again and enter a valid number. \n\n";
		cout << setw(15) << "" << setw(30) << left << "ANSWER";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	searchIds(id, index, found);
	if (found)
		displayCustomerInfo(index);
	else 
		cout << setw(18) << "" << "There are no customers with that customer ID. \n\n";
}

void Customer_List::displayCustomerInfo(int index, int sortingChoice) {
	if (sortingChoice == 1) {
		cout << setw(15) << "" << setw(5) << setfill('0') << right << sortedIdVec[index].customerId << setfill(' ') << setw(10) << "";
		cout << setw(30) << left << sortedIdVec[index].customerName;
		cout << setw(35) << left << sortedIdVec[index].customerAddress;
	}
	else {
		cout << setw(15) << "" << setw(5) << setfill('0') << right << sortedNameVec[index].customerId << setfill(' ') << setw(10) << "";
		cout << setw(30) << left << sortedNameVec[index].customerName;
		cout << setw(35) << left << sortedNameVec[index].customerAddress;
	}
	cout << "\n";
}

void Customer_List::displayCustomerInfo(int index) {
	cout << "\n";
	cout << setw(15) << "" << setw(30) << left << "CUSTOMER ID" << setw(5) << setfill('0') << right << sortedIdVec[index].customerId << setfill(' ') << "\n";
	cout << setw(15) << "" << setw(30) << left << "CUSTOMER NAME" << sortedIdVec[index].customerName << "\n";
	cout << setw(15) << "" << setw(30) << left << "ADDRESS" << sortedIdVec[index].customerAddress << "\n\n";
}

void Customer_List::displayAllCustomers() {
	int choice = displayByIdOrName();

	cout << setw(15) << "" << setw(15) << left << "ID";
	cout << setw(30) << left << "Customer Name";
	cout << setw(35) << left << "Customer Address" << endl << endl;

	if (choice == 1) {
		for (int i = 0; i < customerCount; i++)
			displayCustomerInfo(i, choice);
	}
	else {
		insertionSort();
		for (int i = 0; i < customerCount; i++)
			displayCustomerInfo(i, choice);
	}
}

int Customer_List::displayByIdOrName() {
	int choice;
	cout << setw(15) << "" << "Choose your preferred sorting order: \n";
	cout << setw(20) << "" << "[1] By ID \n";
	cout << setw(20) << "" << "[2] By Name \n";
	inputValidation(choice, 1, 2);
	return choice;
}

void Customer_List::insertionSort() {
	int i, j;
	for (i = 1; i < customerCount; i++) {
		string name = sortedNameVec[i].customerName; 
		int id = sortedNameVec[i].customerId;
		string address = sortedNameVec[i].customerAddress;
		j = i - 1;

		while (j >= 0 && sortedNameVec[j].customerName > name) {
			sortedNameVec[j + 1].customerId = sortedNameVec[j].customerId;
			sortedNameVec[j + 1].customerName = sortedNameVec[j].customerName;
			sortedNameVec[j + 1].customerAddress = sortedNameVec[j].customerAddress;
			j = j - 1;
		}
		sortedNameVec[j + 1].customerName = name;
		sortedNameVec[j + 1].customerId = id;
		sortedNameVec[j + 1].customerAddress = address;
	}
}

int Customer_List::binarySearch(int searchKey, int beginning, int end) {
	while (beginning <= end) {
		int middle = (beginning + end) / 2;
		if (sortedIdVec[middle].customerId == searchKey) {
			return middle;
		}
		else if (sortedIdVec[middle].customerId > searchKey) {
			end = middle - 1;
		}
		else {
			beginning = middle + 1;
		}
	}
	return -1;
}

string Customer_List::searchIds(int id, int& index, bool& found) {
	found = false;
	index = binarySearch(id, 0, customerCount-1);
	if (index != -1) {
		found = true;
		return sortedIdVec[index].customerName;
	}
	else return "";
}

int Customer_List::searchNames(string name, int& index, bool& found) {
	found = false;
	for (index = 0; index < customerCount; ++index) {
		if (sortedNameVec[index].customerName == name) {
			found = true;
			return sortedNameVec[index].customerId;
		}
	}
	return -1;
}

void Customer_List::exitCustomers() {
	ofstream outfile;
	outfile.open("customer_library.txt");
	for (int i = 0; i < sortedIdVec.size(); i++) {
		outfile << sortedIdVec[i].customerId;
		outfile << endl;
		outfile << sortedIdVec[i].customerName;
		outfile << endl;
		outfile << sortedIdVec[i].customerAddress;
		if (sortedIdVec.size() - i != 1) {
			outfile << endl;
		}
	}
	outfile.close();
}
