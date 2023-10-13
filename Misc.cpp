#include "Misc.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace std;

void loadFiles(vector<string>& models, vector<int>& ids, Car_List& canonRental, Customer_List& customers, Renting_Customers& renting) {
	ifstream infile;
	infile.open("car_list.txt");
	if (!infile) {
		cout << "The input file does not exist. Please make sure the input file exists then re-run the program. \n";
		return;
	}
	createCarList(infile, canonRental, models, ids);
	infile.close();
	canonRental.createVideoReference(models, ids);

	infile.open("customer_library.txt");
	if (!infile) {
		cout << "The input file does not exist. Please make sure the input file exists then re-run the program. \n";
		return;
	}
	createCustomerList(infile, customers);
	infile.close();

	infile.open("renting_customers.txt");
	if (!infile) {
		cout << "The input file does not exist. Please make sure the input file exists then re-run the program. \n";
		return;
	}
	createRentingList(infile, renting);
	infile.close();

}

void inputValidation(int& choice, int smallest, int largest) {

	while (true) {
		try {
			cout << endl << setw(15) << "" << setw(30) << left << "Your choice: ";
			cin >> choice;
			if (choice < smallest || choice > largest) throw (0);

			cout << "\n";
			break;
		}
		catch (...) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\n" << setw(15) << "" << "Invalid choice! Please try again. \n";
		}
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

int inputNameOrCode(string &modelKey, int& codeKey) {
	int choice;
	bool validation = false;
	
	cout << setw(15) << "" << "Would you like to do this by using: \n\n";
	cout << setw(20) << "" << "[1] The car name \n";
	cout << setw(20) << "" << "[2] The car code \n";

	inputValidation(choice, 1, 2);

	if (choice == 1) {
		cout << setw(15) << "" << setw(30) << left << "Enter the name of the car:";
		getline(cin, modelKey);
	}
	else {
		cout << setw(15) << "" << setw(30) << left << "Enter the ID of the car:";
		while (!(cin >> codeKey)) {
			cout << setw(18) << "" << "Error: Invalid ID. Please try again and enter a valid number. \n \n";
			cout << setw(15) << "" << setw(30) << left << "ANSWER:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return choice;
}

void landingMenu() {
	cout << "\n";
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                             CANON CAR RENTAL SERVICE                             ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                                   Are you a/an:                                  ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                                   [1] Employee                                   ::" << endl;
	cout << "             ::                                   [2] Customer                                   ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "\n ";
}

void displayMenuEmployee() {
	system("CLS");
	cout << "\n";
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                                   EMPLOYEE MENU                                  ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;		
	cout << "             ::                                [1] Add a new car                                 ::" << endl;	  
	cout << "             ::                                  [2] Rent a car                                  ::" << endl;    
	cout << "             ::                                 [3] Return a car                                 ::" << endl;    
	cout << "             ::                                [4] Check car specs                               ::" << endl;    
	cout << "             ::                               [5] Display all cars                               ::" << endl;	    
	cout << "             ::                        [6] Show list of cars in the garage                       ::" << endl;
	cout << "             ::                            [7] Check car availability                            ::" << endl;	
	cout << "             ::                               [8] Modify car stock                               ::" << endl;		
	cout << "             ::                             [9] Customer maintenance                             ::" << endl;
	cout << "             ::                                 [10] Quit program                                ::" << endl;		
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "\n ";
}

void displayMenuCustomer() {
	system("CLS");
	cout << "\n";
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                                   CUSTOMER MENU                                  ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                    [1] Show complete list of cars with details                   ::" << endl;		
	cout << "             ::                                  [2] Rent a car                                  ::" << endl;		
	cout << "             ::                                 [3] Return a car                                 ::" << endl;		
	cout << "             ::                           [4] Check car availability                             ::" << endl;
	cout << "             ::                                [5] Check car specs                               ::" << endl;
	cout << "             ::                                 [6] Quit program                                 ::" << endl;		
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "\n ";
}

void customerDetails() {
	system("CLS");
	cout << "\n";
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                              CUSTOMER MAINTENANCE                                ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ::                             [1] Add a new customer                               ::" << endl;
	cout << "             ::                        [2] Show a customer's information                         ::" << endl;
	cout << "             ::                    [3] Print a list of all customers details                     ::" << endl;
	cout << "             ::                  [4] Show list of currently renting customers                    ::" << endl;
	cout << "             ::                      [5] Show cars rented by a customer                          ::" << endl;
	cout << "             ::                                [6] Back to menu                                  ::" << endl;
	cout << "             ::                                                                                  ::" << endl;
	cout << "             ======================================================================================" << endl;
	cout << "\n ";
}

void createCarList(ifstream& infile, Car_List& canonRental, vector<string>& models, vector<int>& ids) {
	string tempModel, tempManufacturer, tempFuelType, tempBodyType, tempTransmission;
	int tempcode;
	int tempReleased, tempStock, tempOwned;
	char buf;

	while (infile) {
		getline(infile, tempModel);
		infile >> tempcode;
		infile.get(buf);
		getline(infile, tempManufacturer);
		getline(infile, tempTransmission);
		getline(infile, tempBodyType);
		getline(infile, tempFuelType);
		infile >> tempReleased;
		infile.get(buf);
		infile >> tempOwned;
		infile.get(buf);
		infile >> tempStock;
		infile.get(buf);
		canonRental.insertVideo(tempModel, tempcode, tempManufacturer, tempTransmission, tempBodyType, tempFuelType, tempReleased, tempOwned, tempStock, models, ids);
		if (infile.eof()) break;
	}
}

void createCustomerList(ifstream& infile, Customer_List& customers) {
	string tempModel, tempAddress;
	int tempcode;
	char buf;

	while (infile) {
		infile >> tempcode;
		infile.get(buf);
		getline(infile, tempModel);
		getline(infile, tempAddress);
		customers.addToVectors(tempcode, tempModel, tempAddress);
		if (infile.eof()) break;
	}
}

void createRentingList(ifstream& infile, Renting_Customers& renting) {
	int tempid, temptotal, holder;
	char buf;

	while (infile) {
		if (infile.eof()) break;
		infile >> tempid;
		infile.get(buf);
		infile >> temptotal;
		vector<int> vec;
		for (int i = 0; i < temptotal; i++) {
			infile >> holder;
			vec.push_back(holder);
			infile.get(buf);
		}
		renting.addNewRenter(tempid, temptotal, vec);
	}
}

void exitProgram(Car_List canonRental, Customer_List customers, Renting_Customers renting) {
	canonRental.terminateOption();
	customers.exitCustomers();
	renting.exitRenters();

}