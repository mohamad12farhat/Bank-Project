#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";

using namespace std;
class clsDeleteScreen : protected clsScreen
{
	static void _printClient(clsBankClient client)
	{
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
	static void showDeleteClientScreen() 
	{

		if (!checkAccessright(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		_drawScreenHeader("\t Delete Client Screen");

		

		string accountNumber = "";

		cout << "Please enter account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber)) {
			cout << "Account does not exist, please enter another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);
		_printClient(client);

		char answer = 'y';
		cout << "\n\nAre you sure do you want to delete this client? (yes for y and n for no)?: ";
		cin >> answer;

		if (tolower(answer) == 'y') {
			if (client.deleteClient()) {
				cout << "\nClient Deleted Successfully..";
				_printClient(client);
				
			}
			else {
				cout << "\nError client was not deleted";
			}
		}
	}
};

