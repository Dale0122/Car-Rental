#include "Car.h"
#include "Misc.h"
#include "Rented.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace std;

bool Car_List::isEmpty(car* head) {
	if (head == NULL)
		return true;
	else return false;
}
void Car_List::parkNewCar(vector<string>& models, vector<int>& ids) {

	string tempModel, tempManufacturer, tempTransmission, tempBodyType, tempFuelType;
	int tempReleased, tempStock;
	bool found;
	car* location;
	car* previous_location;

	cout << endl;
	cout << setw(15) << "" << "Please enter the details of the car you would like to add to the list. \n\n"; 
	cout << setw(20) << "" << setw(25) << left << "CAR ID: " << setw(5) << setfill('0') << right << totalVehicles + 1 << setfill(' ') << endl << endl;
	cout << setw(20) << "" << setw(25) << left << "CAR MODEL";
	getline(cin, tempModel);
	searchVehicleList(tempModel, found, location, previous_location);
	if (found) {
		cout << setw(15) << "" << "Error: A car with this name already exists within the database. Please try again from the beginning.  \n" <<
			setw(15) << "" << "If you wish to modify the stocks of a particular car, select ""Modify Stock"" in the main menu. \n";
		return;
	}

	cout << setw(20) << "" << setw(25) << left << "Manufacturer";
	getline(cin, tempManufacturer);

	cout << setw(20) << "" << setw(25) << left << "Transmission";
	getline(cin, tempTransmission);

	cout << setw(20) << "" << setw(25) << left << "Body Type";
	getline(cin, tempBodyType);

	cout << setw(20) << "" << setw(25) << left << "Fuel Type";
	getline(cin, tempFuelType);

	cout << setw(20) << "" << setw(25) << left << "Year Released";
	while (!(cin >> tempReleased)) {
		cout << endl << setw(15) << "" << "Error: Invalid year. Please enter another. \n\n";
		cout << setw(20) << "" << setw(25) << left << "Year Released";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << setw(20) << "" << setw(25) << left << "How many in stock?";
	while (!(cin >> tempStock)) {
		cout << endl << setw(15) << "" << "Error: Not a valid number. Try again. \n\n";
		cout << setw(20) << "" << setw(25) << left << "How many in stock?:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int tempcode = totalVehicles + 1;

	if (tempModel == "" || tempManufacturer == "" || tempTransmission == "" || tempBodyType == "" || tempFuelType == "") {
		cout << setw(15) << "" << "Adding failed: Information incomplete. \n";
		return;
	}
	if (tempReleased < 1500 || tempReleased > 2030) {
		cout << setw(15) << "" << "Adding failed: Invalid year. \n";
		return;
	}
	if (tempStock < 0) {
		cout << setw(15) << "" << "Adding failed: Cannot have stock below 0. \n";
		return;
	}

	insertVideo(tempModel, tempcode, tempManufacturer, tempTransmission, tempBodyType, tempFuelType, tempReleased, tempStock, tempStock, models, ids);
	cout << endl << setw(15) << "" << "Car successfully parked!\n\n";
}
void Car_List::checkAvailability() {
	int codeKey, type;
	string modelKey;
	type = inputNameOrCode(modelKey, codeKey);

	bool found;
	car* location;
	car* previous_location;

	if (type == 1)
		searchVehicleList(modelKey, found, location, previous_location);
	else
		searchVehicleList(codeKey, found, location, previous_location);

	if (!found) {
		cout << setw(15) << "" << "Oh, no! We're sorry - we do not currently have that car in our garage. \n";
		return;
	}
	cout << "\n";
	cout << setw(15) << "" << setw(20) << left << "CAR ID" << setw(5) << setfill('0') << right << location->vehicleId << setfill(' ') << "\n";
	cout << setw(15) << "" << setw(20) << left << "MODEL" << location->vehicleModel << "\n";
	cout << setw(15) << "" << setw(20) << left << "CAR MANUFACTURER" << location->manufacturer << "\n";
	cout << setw(15) << "" << setw(20) << left << "DIRECTED BY" << location->vehicleTransmission << "\n";
	cout << setw(15) << "" << setw(20) << left << "DISTRIBUTED BY" << location->vehicleBodyType << "\n";
	cout << setw(15) << "" << setw(20) << left << "TOTAL COPIES OWNED" << location->totalOwned << "\n";
	cout << setw(15) << "" << setw(20) << left << "TOTAL IN STOCK" << location->totalInStock << "\n";
	cout << setw(15) << "" << setw(20) << left << "AVAILABILITY" << (location->totalInStock > 0 ? "AVAILABLE!" : "Not Available") << endl;
}

void Car_List::displayCarSpecs() {
	int codeKey, type;
	string modelKey;
	type = inputNameOrCode(modelKey, codeKey);

	bool found;
	car* location;
	car* previous_location;

	if (type == 1)
		searchVehicleList(modelKey, found, location, previous_location);
	else
		searchVehicleList(codeKey, found, location, previous_location);

	if (found) {
		cout << "\n\n";
		cout << setw(15) << "" << "The car details for this car are as follows: \n\n";
		cout << setw(15) << "" << setw(20) << left << "CAR ID" << setw(5) << setfill('0') << right << location->vehicleId << setfill(' ') << "\n";
		cout << setw(15) << "" << setw(20) << left << "MODEL" << location->vehicleModel << "\n";
		cout << setw(15) << "" << setw(20) << left << "CAR MANUFACTURER" << location->manufacturer << "\n";
		cout << setw(15) << "" << setw(20) << left << "TRANSMISSION" << location->vehicleTransmission << "\n";
		cout << setw(15) << "" << setw(20) << left << "BODY TYPE" << location->vehicleBodyType << "\n";
		cout << setw(15) << "" << setw(20) << left << "MODEL YEAR" << location->releaseYear << "\n";
		cout << setw(15) << "" << setw(20) << left << "FUEL TYPE" << location->vehicleFuelType << "\n";
		cout << setw(15) << "" << setw(20) << left << "TOTAL OWNED" << location->totalOwned << "\n";
		cout << setw(15) << "" << setw(20) << left << "IN OUR GARAGE NOW" << location->totalInStock << "\n\n";
	}
	else 
		cout << setw(15) << "" << "There is no car with that information.";
}

void Car_List::displayAllModels() {
	car* node_pointer;
	if (isEmpty(head))
		cout << setw(15) << "" << "Uh-oh, looks like there are currently no cars in the garage. \n";
	else {
		cout << setw(15) << "" << "The cars currently available are... \n\n";
		node_pointer = head;
		while (node_pointer) {
			cout << setw(20) << "" << setw(5) << setfill('0') << right << node_pointer->vehicleId << setfill(' ') << setw(10) << "";
			cout << node_pointer->vehicleModel << endl;
			node_pointer = node_pointer->next;
		}
	}
}

void Car_List::createVideoReference(vector<string>& vec, vector<int>& ids) {
	car* node_pointer;
	node_pointer = head;
	while (node_pointer) {
		vec.push_back(node_pointer->vehicleModel);
		ids.push_back(node_pointer->vehicleId);
		node_pointer = node_pointer->next;
	}
}

void Car_List::displayAllCarSpecs() {
	car* node_pointer;
	if (isEmpty(head))
		cout << setw(15) << "" << "Uh-oh, looks like there are currently no cars in the garage. \n";
	else {
		cout << setw(15) << "" << "The cars currently available are... \n\n";
		node_pointer = head;

		cout << setw(15) << "" << setw(15) << left << "CAR ID" << setw(30) << left << "MODEL" << setw(30) << left << "MANUFACTURER"
			<< setw(30) << left << "BODY TYPE" << setw(30) << left << "TRANSMISSION" << "YEAR \n\n";

		while (node_pointer) {
			cout << setw(15) << "" << setw(5) << setfill('0') << right << node_pointer->vehicleId << setfill(' ') << setw(10) << "";
			cout << setw(30) << left << node_pointer->vehicleModel;
			cout << setw(30) << left << node_pointer->manufacturer;
			cout << setw(30) << left << node_pointer->vehicleBodyType;
			cout << setw(30) << left << node_pointer->vehicleTransmission;
			cout << setw(10) << left << node_pointer->releaseYear;
			cout << "\n";

			node_pointer = node_pointer->next;
		}
	}
}

void Car_List::modifyStock() {
	int codeKey, type, stock;
	string modelKey;
	bool found;
	car* location;
	car* previous_location;

	type = inputNameOrCode(modelKey, codeKey);

	if (type == 1)
		searchVehicleList(modelKey, found, location, previous_location);
	else
		searchVehicleList(codeKey, found, location, previous_location);

	if (found) {
		cout << endl;
		cout << setw(15) << "" << "How many stocks would you like to park (or remove)? \n";
		cout << setw(15) << "" << "Note: If you wish to subtract from the stock, include a negative sign. \n";
		cout << setw(20) << "" << "e.g. 10, -10, -15 \n\n";
		cout << setw(25) << "" << setw(20) << left << "Number:";

		while (!(cin >> stock)) {
			cout << setw(18) << "" << "ERROR. Please try again and enter a valid number. \n\n";
			cout << setw(15) << "" << setw(20) << left << "Number:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (location->totalInStock + stock < 0) {
			cout << setw(15) << "" << "ERROR. You attempted to subtract more than what is currently in stock.  \n" <<
				setw(15) << "" << "Loading back to the main menu. \n";
			return;
		}
		else {
			location->totalInStock += stock;
			location->totalOwned += stock;
			cout << endl << setw(15) << "" << "Stock has been modified.\n" << 
				setw(15) << "" << "There are now " << location->totalInStock << " parked in the garage of the car model: " << location->vehicleModel << "\n";
		}
	}
	else 
		cout << "\n" << setw(15) << "" << "There is no car with that information in our garage. \n\n";
}

void Car_List::enterCustomerId(int& customerId, Customer_List customers, Renting_Customers renting) {
	int index = 0;
	bool found;

	while (true) {
		cout << setw(15) << "" << setw(30) << left << "Enter customer's ID:";
		while (!(cin >> customerId)) {
			cout << endl << setw(15) << "" << "Error: Invalid customer ID. \n" << setw(15) << "" << "Please enter a valid number or enter 0 to exit the rent/return dialog. \n\n";
			cout << setw(15) << "" << setw(30) << left << "ANSWER:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (customerId == 0)
			break;
		else if ((customers.searchIds(customerId, index, found)) == "")
			cout << endl << setw(15) << "" << "There are no customers with that ID. \n" << setw(15) << "" << "Please try again or enter 0 to exit the rent/return dialog. \n\n";
		else
			break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if (customerId == 0) {
		cout << endl << setw(15) << "" << "You have opted to exit the rent/return dialog. \n" << setw(15) << "" << "Loading you back to the main menu. \n\n";
		return;
	}
	customers.displayCustomerInfo(index);
}

void Car_List::rentCar(Customer_List& customers, Renting_Customers& renting) {
	int customerId;
	bool found;

	enterCustomerId(customerId, customers, renting);
	if (customerId == 0) return;
	
	int type, codeKey, choice = 1;
	string modelKey;
	car* location;
	car* previous_location;
	
	while (choice != 2) {
		type = inputNameOrCode(modelKey, codeKey);
		if (type == 1)
			searchVehicleList(modelKey, found, location, previous_location);
		else
			searchVehicleList(codeKey, found, location, previous_location);

		if (found) {
			if (location->totalInStock > 0) {
				--(location->totalInStock);
				renting.addToRented(customerId, location->vehicleId);
				cout << "\n";
				cout << setw(15) << "" << "Car successfully rented! Current stock has been updated: \n\n";
				cout << setw(20) << "" << setw(25) << left << "CAR ID" << setw(5) << setfill('0') << right << location->vehicleId << setfill(' ') << "\n";
				cout << setw(20) << "" << setw(25) << left << "MODEL" << location->vehicleModel << "\n";
				cout << setw(20) << "" << setw(25) << left << "TOTAL IN STOCK" << location->totalInStock << "\n\n";
			}
			else
				cout << setw(15) << "" << "Oh, no! This car is currently out of stock. \n\n";
		}
		else
			cout << setw(15) << "" << "Oh, no! That car isn't currently in our garage. \n\n";

		cout << setw(15) << "" << "Rent another car by the same customer? \n";
		cout << setw(20) << "" << "[1] Yes. \n";
		cout << setw(20) << "" << "[2] No. \n";
		inputValidation(choice, 1, 2);
	}
}

void Car_List::returnCar(Customer_List& customers, Renting_Customers& renting) {
	int customerId;
	bool found;

	enterCustomerId(customerId, customers, renting);
	if (customerId == 0) return;

	int codeKey, choice = 1;
	bool success;
	car* location;
	car* previous_location;

	while (choice == 1) {
		cout << setw(15) << "" << setw(30) << left << "Enter the ID of the car:";

		while (!(cin >> codeKey)) {
			cout << setw(15) << "" << "Error: Invalid ID. Please try again and enter a valid number.  \n\n";
			cout << setw(15) << "" << setw(30) << left << "ANSWER:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		searchVehicleList(codeKey, found, location, previous_location);
		if (found) {
			success = renting.removeFromRented(customerId, codeKey);
			if (success) {
				++(location->totalInStock);
				cout << "\n" << setw(15) << "" << "Car successfully returned! \n\n";
			}
		}
		else {
			cout << setw(15) << "" << "ERROR: We do not have that car in our garage.";
		}

		cout << setw(15) << "" << "Return another car from the same customer? \n";
		cout << setw(20) << "" << "[1] Yes. \n";
		cout << setw(20) << "" << "[2] No. \n";
		inputValidation(choice, 1, 2);
	}
}

void Car_List::insertVideo(string name, int code, string manufacturer, string vehicleTransmission, string bodytype, string fueltype, int released, int owned, int stock, vector<string>& models, vector<int>& ids) {

	car* new_node = new car;
	new_node->vehicleModel = name;
	new_node->vehicleId = code;
	new_node->manufacturer = manufacturer;
	new_node->vehicleTransmission = vehicleTransmission;
	new_node->vehicleBodyType = bodytype;
	new_node->vehicleFuelType = fueltype;
	new_node->releaseYear = released;
	new_node->totalOwned = owned;
	new_node->totalInStock = stock;
	new_node->next = NULL;
	if (isEmpty(head)) 
		head = new_node;
	else 
		last->next = new_node;
	last = new_node;
	ids.push_back(code);
	models.push_back(name);
	++totalVehicles;
}

void Car_List::searchVehicleList(string key, bool& found, car*& current, car*& previous_location) {
	found = false;
	current = head;
	while (current != NULL && !found) {
		if (current->vehicleModel == key) {
			found = true;
		}
		else {
			previous_location = current;
			current = current->next;
		}
	}
}

void Car_List::searchVehicleList(int key, bool& found, car*& current, car*& previous_location) {
	found = false;
	current = head;
	while (current != NULL && !found) {
		if (current->vehicleId == key) {
			found = true;
		}
		else {
			previous_location = current;
			current = current->next;
		}
	}
}

void Car_List::terminateOption() {
	ofstream outfile;
	car* node_pointer;
	node_pointer = head;
	outfile.open("car_list.txt");
	while (node_pointer) {
		outfile << node_pointer->vehicleModel;
		outfile << endl;
		outfile << node_pointer->vehicleId;
		outfile << endl;
		outfile << node_pointer->manufacturer;
		outfile << endl;
		outfile << node_pointer->vehicleTransmission;
		outfile << endl;
		outfile << node_pointer->vehicleBodyType;
		outfile << endl;
		outfile << node_pointer->vehicleFuelType;
		outfile << endl;
		outfile << node_pointer->releaseYear;
		outfile << endl;
		outfile << node_pointer->totalOwned;
		outfile << endl;
		outfile << node_pointer->totalInStock;
		if (node_pointer->next) 
			outfile << endl;
		node_pointer = node_pointer->next;
	}
	outfile.close();
}