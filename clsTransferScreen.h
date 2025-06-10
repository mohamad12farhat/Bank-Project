#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;
class clsTransferScreen : protected clsScreen 
{

	static void _printClientCard(clsBankClient client)
	{
		cout << "\n\nClient Card:";
		cout << "\n___________________________________________\n";
		cout << "\nFull Name   :" << client.getFullName();
		cout << "\nAcc Number  :" << client.getAccountNumber();
		cout << "\nAcc Balance :" << client.AccountBalance;
		cout << "\n___________________________________________\n";
	}

	static string _readAccountNumber()
	{
		string accountNumber = "";
		cout << "\nPlease enter account number to transfer: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nClient does not exist, please enter another one: ";
			accountNumber = clsInputValidate::ReadString();
		}



		return accountNumber;
	}

	static float _readAmount(clsBankClient sourceClient)
	{
		
		float amount = 0;
		cout << "\nPlease enter transfer amount: ";
		amount = clsInputValidate::ReadFloatNumber();

		while (amount > sourceClient.AccountBalance)
		{
			cout << "\n\nAmount exceeds the available balance, please enter another amount: ";
			amount = clsInputValidate::ReadFloatNumber();
		}
		return amount;
	}

public:

	static void showTransferScreen()
	{
		_drawScreenHeader("\t Transfer Screen");

		
		clsBankClient sourceClient = clsBankClient::find(_readAccountNumber());

		_printClientCard(sourceClient);
		

		
		clsBankClient destinationClient = clsBankClient::find(_readAccountNumber());
		

		_printClientCard(destinationClient);

		float amount = _readAmount(sourceClient);

		char answer = 'y';
		cout << "\n\nAre you sure do you want to perform this operation? (y for yes and n for no)?: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (sourceClient.transfer(amount, destinationClient,CurrentUser.Username))
			{
				cout << "\n\nAmount transfered successfully.\n";
			}
			else
			{
				cout << "\n\nError, Amount was not transfered.\n";
			}
		}

		_printClientCard(sourceClient);
		_printClientCard(destinationClient);
		
	}
};

