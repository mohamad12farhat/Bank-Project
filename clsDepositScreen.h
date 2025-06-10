#pragma once
#include <iostream>
#include "clsTransactionScreen.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";
using namespace std;
class clsDepositScreen : protected clsScreen
{

	static void _printClient(clsBankClient client) {
		cout << "\n\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirst Name  :" << client.getFirstName();
		cout << "\nLast Name   :" << client.getLastName();
		cout << "\nFull Name   :" << client.getFullName();
		cout << "\nEmail       :" << client.getEmail();
		cout << "\nPhone       :" << client.getPhoneNumber();
		cout << "\nAcc Number  :" << client.getAccountNumber();
		cout << "\nPin Code    :" << client.getPinCode();
		cout << "\nAcc Balance :" << client.getAccountBalance();
		cout << "\n___________________\n";
	}
public:
	static void showDepositScreen() {

		_drawScreenHeader("\t Deposit Screen");

		

		string accountNumber = "";

		cout << "\nPlease enter account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber)) {
			cout << "\n\nClient with [" << accountNumber << "] does not exist\n";
			cout << "\nPlease enter account number: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);
		_printClient(client);

		double amount = 0;
		cout << "\nPlease etner deposit amount: ";
		amount = clsInputValidate::ReadDblNumber();

		char answer = 'y';
		cout << "\n\nAre you sure do you want to perform this transaction? (y for yes and n for no): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			client.deposit(amount);
			cout << "\nAmount deposit successfully!!!\n";
			cout << "\nNew Balance is: " << client.getAccountBalance();
			
		}
		else {
			cout << "\nOperation cancelled.\n";
		}


	}
};

