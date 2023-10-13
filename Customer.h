#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Customer_List {
private:
	struct CustomerInfo	{
		int customerId = 0;
		string customerName;
		string customerAddress;

		CustomerInfo() {}
		CustomerInfo(int id, string name, string address)
			: customerId(id), customerName(name), customerAddress(address)
			{}
	};
	vector<CustomerInfo> sortedIdVec;
	vector<CustomerInfo> sortedNameVec;

	void insertionSort();
	void inputCustomerInfo(string& name, string& address);
	int displayByIdOrName();

public:
	int customerCount = 0;
	void exitCustomers();

	string searchIds(int id, int& index, bool& found);
	int searchNames(string name, int& index, bool& found);
	int binarySearch(int searchKey, int beginning, int end);

	void addNewCustomer();
	void addToVectors(int code, string name, string address);

	void checkOneCustomer();
	void displayCustomerInfo(int index, int sortingChoice);
	void displayCustomerInfo(int index);
	void displayAllCustomers();
};


