#include "Rented.h"
#include "Car.h"
#include <fstream>


void Renting_Customers::addNewRenter(int id, int total, vector<int> vec) {
	Renting* new_node = new Renting;
	new_node->customerId = id;
	new_node->currentlyRenting = total;
	for (int i = 0; i < total; i++) 
		new_node->carIDs.push_back(vec[i]);
	new_node->next = NULL;

	if (isEmpty(head)) 
		head = new_node;
	else 
		last->next = new_node;
	last = new_node;
}

bool Renting_Customers::isEmpty(Renting* head) {
	if (head == NULL)
		return true;
	else return false;
}

bool Renting_Customers::isRentingCar(int customerId, int carID, Renting*& current, Renting*& previous) {
	bool found;
	searchRentingCustomers(customerId, found, current, previous);

	if (found) {
		found = false;
		for (auto e : current->carIDs) {
			if (carID == e) {
				found = true;
				break;
			}
		}
	}
	return found;
}

void Renting_Customers::searchRentingCustomers(int key, bool &found, Renting*& current, Renting *& previous_location) {
	if (isEmpty(head)) {
		current = NULL;
		return;
	}
	found = false;
	current = head;
	while (current != NULL && !found) {
		if (current->customerId == key) {
			found = true;
		}
		else {
			previous_location = current;
			current = current->next;
		}
	}
}

void Renting_Customers::deleteCustomer(Renting*& location, Renting*& previous) {
	if (location == head) {
		if (location == last) {
			head = NULL;
			last = NULL;
		}
		else {
			head = location->next;
		}
	}
	else if (location == last) {
		previous->next = NULL;
		last = previous;
	}
	else {
		previous->next = location->next;
	}

	delete location;

}

void Renting_Customers::addToRented(int id, int vehicleId) {
	bool found;
	Renting* current;
	Renting* previous;
	searchRentingCustomers(id, found, current, previous);

	if (found) {
		++(current->currentlyRenting);
		current->carIDs.push_back(vehicleId);
	}
	else {
		vector<int> temp = { vehicleId };
		addNewRenter(id, 1, temp);
	}
}

bool Renting_Customers::removeFromRented(int customerId, int carID) {
	Renting* current;
	Renting* previous;
	bool isRenting = isRentingCar(customerId, carID, current, previous);
	if (!isRenting) {
		cout << endl << setw(15) << "" << "ERROR. Customer #" << customerId << " is not currently renting a car with that ID.\n\n";
		return false;
	}
	else {
		--(current->currentlyRenting);
		current->carIDs.erase(remove(current->carIDs.begin(), current->carIDs.end(), carID), current->carIDs.end());    

		if (current->currentlyRenting == 0)
			deleteCustomer(current, previous);
		
		return true;
	}
}

void Renting_Customers::displayCarsRented(int customerId, Customer_List customers, vector<string> models, vector<int> ids) {
	if (isEmpty(head)) {
		cout << setw(15) << "" << "There are currently no cars being rented right now. \n\n";
		return;
	}

	bool found;
	Renting* current;
	Renting* previous;
	searchRentingCustomers(customerId, found, current, previous);

	if (!found) {
		cout << setw(15) << "" << "Customer #" << customerId << " is not renting any cars right now. \n\n";
		return;
	}
	else {
		int search = customers.binarySearch(customerId, 0, customers.customerCount);
		customers.displayCustomerInfo(search);

		cout << "\n" << setw(15) << "" << "Rented: \n\n";
		cout << setw(20) << "" << setw(15) << left << "CAR ID" << setw(20) << left << "CAR MODEL" << endl << endl;

		for (auto e : current->carIDs) {
			for (int i = 0; i < models.size(); i++) {
				if (e == ids[i]) {
					cout << setw(20) << "" << setw(5) << setfill('0') << right << e << setfill(' ') << setw(10) << "" <<
						setw(20) << left << models[i] << "\n";
					break;
				}
			}
		}
	}
}

void Renting_Customers::checkCustomerRent(Customer_List customers, vector<string> models, vector<int> ids) {
	int customerId;
	cout << setw(15) << "" << setw(30) << left << "Enter customer ID";

	while (!(cin >> customerId)) {
		cout << setw(18) << "" << "ERROR. Please try again and enter a valid number. \n\n";
		cout << setw(15) << "" << setw(30) << left << "ANSWER";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	displayCarsRented(customerId, customers, models, ids);

}

void Renting_Customers::displayRentingCustomers(Customer_List customers) {
	Renting* node_pointer;
	if (isEmpty(head))
		cout << setw(15) << "" << "There are currently no customers renting from the garage. \n";
	else {
		int index;
		bool found;
		cout << setw(15) << "" << "Customers currently renting from the garage are \n\n";
		node_pointer = head;
		cout << setw(15) << "" << setw(15) << left << "ID";
		cout << setw(30) << left << "Customer Name";
		cout << setw(20) << left << "Currently Renting" << endl << endl;

		while (node_pointer) {
			cout << setw(15) << "" << setw(5) << setfill('0') << right << node_pointer->customerId << setfill(' ') << setw(10) << "";
			cout << setw(30) << left << customers.searchIds(node_pointer->customerId, index, found);
			cout << node_pointer->currentlyRenting << (node_pointer->currentlyRenting > 1 ? " vehicles\n" : " car\n");

			node_pointer = node_pointer->next;
		}
	}
}

void Renting_Customers::exitRenters() {
	ofstream outfile;
	Renting* node_pointer;
	node_pointer = head;
	outfile.open("renting_customers.txt");
	while (node_pointer) {
		outfile << node_pointer->customerId;
		outfile << endl;
		outfile << node_pointer->currentlyRenting;
		outfile << endl;
		for (int i = 0; i < node_pointer->currentlyRenting; i++) {
			outfile << node_pointer->carIDs[i];
			outfile << (node_pointer->currentlyRenting - i != 1 ? " " : "");
		}
		if (node_pointer->next) {
			outfile << endl;
		}
		node_pointer = node_pointer->next;
	}
	outfile.close();
}
