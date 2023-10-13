#pragma once
#include <string>
#include <iostream>
#include "Rented.h"
using namespace std;

class Car_List {
private:
	struct car {
		string vehicleModel;
		int vehicleId;
		string vehicleTransmission;
		string manufacturer;
		string vehicleBodyType;
		string vehicleFuelType;
		int releaseYear;
		int totalOwned;
		int totalInStock;
		car* next;
	};
	car* head = NULL;
	car* last = NULL;

	int totalVehicles = 0;
	void enterCustomerId(int& customerId, Customer_List customers, Renting_Customers renting);

public:
	void terminateOption();

	bool isEmpty(car* head);
	void checkAvailability();

	void parkNewCar(vector<string>& models, vector<int>& ids);
	void insertVideo(string name, int code, string manufacturer, string vehicleTransmission, string bodytype, string fueltype, int released, int owned, int stock, vector<string>& models, vector<int>& ids);
	void modifyStock(); 

	void searchVehicleList(string key, bool& found, car*& current, car*& previous);
	void searchVehicleList(int key, bool& found, car*& current, car*& previous);

	void rentCar(Customer_List& customers, Renting_Customers& renting);
	void returnCar(Customer_List& customers, Renting_Customers& renting);

	void displayCarSpecs();
	void displayAllCarSpecs();
	void displayAllModels();

	void createVideoReference(vector<string>& vec, vector<int>& ids);
};


