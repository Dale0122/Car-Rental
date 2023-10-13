#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Car.h"
using namespace std;

int inputNameOrCode(string& modelKey, int& codeKey);
void landingMenu();
void displayMenuEmployee();
void displayMenuCustomer();
void customerDetails();
void createCarList(ifstream& infile, Car_List& canonRental, vector<string>& models, vector<int>& ids);
void createCustomerList(ifstream& infile, Customer_List& customers);
void createRentingList(ifstream& infile, Renting_Customers& renting);
void inputValidation(int& choice, int smallest, int largest);
void exitProgram(Car_List canonRental, Customer_List customers, Renting_Customers renting); 
void loadFiles(vector<string>& models, vector<int>& ids, Car_List& canonRental, Customer_List& customers, Renting_Customers& renting);