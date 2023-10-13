#pragma once
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Customer.h"

/* Declaration for the rented customers class/ADT, which will garage all the needed data regarding all customers who
are curerntly rending a car from the car garage, and also numerous methods that can be done to the data such as adding, 
searching, modifying, deleting, and more.

This ADT makes use of a Linked List.*/

class Renting_Customers : public Customer_List {
private:
	struct Renting {
		int customerId;
		int currentlyRenting;
		vector<int> carIDs;

		Renting* next;
	};
	Renting* head = NULL;
	Renting* last = NULL;

	bool isRentingCar(int customerId, int carID, Renting*& current, Renting*& previous); // check if customer is renting the car they're returning
	void searchRentingCustomers(int key, bool& found, Renting*& current, Renting*& previous_location);
	void deleteCustomer(Renting*& location, Renting*& previous);

public:
	void exitRenters();

	bool isEmpty(Renting* head);
	void addNewRenter(int id, int total, vector<int> vec); // add new customer to list
	void addToRented(int id, int vehicleId); // general when customer rents a car
	bool removeFromRented(int customerId, int carID); // general when customer returns a car
	void displayCarsRented(int customerId, Customer_List customers, vector<string> models, vector<int> ids);
	void checkCustomerRent(Customer_List customers, vector<string> models, vector<int> ids);
	void displayRentingCustomers(Customer_List customers);
};