#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h"; 
#include "clsBankClient.h";

using namespace std;
class clsWithdrawScreen : protected clsScreen
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
	static void showWithdrawScreen()
	{
		_drawScreenHeader("\t Withdraw Screen");


		string accountNumber = "";
		cout << "\nPlease enter account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount with [" << accountNumber << "] does no exist\n";
			cout << "\nPlease enter account number: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);
		_printClient(client);

		double amount = 0;
		cout << "\nPlease enter withdraw amount: ";
		amount = clsInputValidate::ReadDblNumber();

		char answer = 'y';
		cout << "\n\nAre you sure do you want to perform this transaction(y for yes and n for no)? : ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (client.withdraw(amount))
			{
				cout << "\nAmount Withdrew Successfully..\n";
				cout << "\nNew Balance is: " << client.getAccountBalance() << endl;
			}
			else {
				cout << "\nCannot withdaraw, insufficient balance!!\n";
				cout << "\nAmount to withdraw is: " << amount;
				cout << "\n\nAmount in your balance: " << client.getAccountBalance() << endl;
			}
		}
	}
};

