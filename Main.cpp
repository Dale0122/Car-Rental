#include <iostream>
#include "Misc.h"
#include "Car.h"
#include "Customer.h"
#include "Rented.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {

	vector<string> models;
	vector<int> ids;
	Car_List canonRental;
	Customer_List customers;
	Renting_Customers renting;

	loadFiles(models, ids, canonRental, customers, renting);

	int choice = 0, choiceTwo = 0, employeeOrCustomer;
	landingMenu();
	do {
		inputValidation(employeeOrCustomer, 1, 2);

		if (employeeOrCustomer == 1) { 
			while (choice != 10) {
				choiceTwo = 0;
				displayMenuEmployee();
				inputValidation(choice, 1, 10);
				
				system("CLS");
				cout << endl << endl;
				switch (choice) {
					case 1:
						canonRental.parkNewCar(models, ids);
						break;
					case 2:
						canonRental.rentCar(customers, renting);
						break;
					case 3:
						canonRental.returnCar(customers, renting);
						break;
					case 4:
						canonRental.displayCarSpecs();
						break;
					case 5:
						canonRental.displayAllCarSpecs();
						break;
					case 6:
						canonRental.displayAllModels();
						break;
					case 7:
						canonRental.checkAvailability();
						break;
					case 8:
						canonRental.modifyStock();
						break;
					case 9:
						while (choiceTwo != 6) {
							customerDetails();
							inputValidation(choiceTwo, 1, 6);

							switch (choiceTwo) {
								case 1:
									customers.addNewCustomer();
									break;
								case 2:
									customers.checkOneCustomer();
									break;
								case 3:
									customers.displayAllCustomers();
									break;
								case 4:
									renting.displayRentingCustomers(customers);
									break;
								case 5:
									renting.checkCustomerRent(customers, models, ids);
									break;
								case 6:
									break;
							}
							if (choiceTwo != 6) {
								cout << "\n\n" << setw(15) << "";
								system("pause");
							}
						}
						break;
					case 10:
						cout << setw(15) << "" << "Thank you for your patronage! Now exiting.\n\n";
						cout << setw(15) << "";
						system("pause");
						exitProgram(canonRental, customers, renting);
						return 0;
					default:
						// fix formatting
						cout << setw(15) << "" << "NOT A VALID CHOICE!"
				}
				cout << endl << setw(15) << "";
				system("pause");
			}
		}
		else {						
			while (choice != 6) {
				choiceTwo = 0;
				displayMenuCustomer();
				inputValidation(choice, 1, 6);

				system("CLS");
				cout << endl << endl;

				switch (choice) {
					case 1:
						canonRental.displayAllCarSpecs();
						break;
					case 2:
						canonRental.rentCar(customers, renting);
						break;
					case 3:
						canonRental.returnCar(customers, renting);
						break;
					case 4:
						canonRental.checkAvailability();
						break;
					case 5:
						canonRental.displayCarSpecs();
						break;
					case 6:
						cout << setw(15) << "" << "Thank you for your patronage! Come back again soon!\n\n";
						cout << setw(15) << "";
						system("pause");
						exitProgram(canonRental, customers, renting);
						return 0;
				}
				cout << endl << setw(15) << "";
				system("pause");
			}
		}
	} while (true);
}