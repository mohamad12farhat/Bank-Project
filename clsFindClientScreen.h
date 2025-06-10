#pragma once
#include <iostream>
#include "clsScreen.h";
using namespace std;

class clsFindClientScreen : protected clsScreen
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

	static void showFindClientScreen() {

		if (!checkAccessright(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		_drawScreenHeader("\t Find Client Screen");

		

		string accountNumber = "";
		cout << "\n\nPlease enter client account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\n\nAccount does not exist, please enter another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);

		if (client.isEmpty()) 
		{
			cout << "Client was not found!!";
		}
		else
		{
			cout << "Client successfully found.";
			
		}
		_printClient(client);
	}
};

