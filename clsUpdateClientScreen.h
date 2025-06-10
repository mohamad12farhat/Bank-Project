#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";
class clsUpdateClientScreen : protected clsScreen
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

	static void _readClientInfo(clsBankClient &client) {


		

		cout << "\nEnter First Name: ";
		client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone Number: ";
		client.PhoneNumber = clsInputValidate::ReadString();

		cout << "\nEnter Pin Code: ";
		client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

public:
	static void showUpdateClientScreen() {

		if (!checkAccessright(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}
		_drawScreenHeader("\t Update Client Screen");

		
		
		string accountNumber = "";
		cout << "\n\nPlease enter client account number: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::isClientExist(accountNumber)) {
			cout << "\n\nAccount does not exist, please enter another one: ";
			accountNumber = clsInputValidate::ReadString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);

		_printClient(client);

		char answer = 'y';
		cout << "\n\nAre you sure do you want to update this client? (y for y and n for no): ";
		cin >> answer;

		if (tolower(answer) == 'y') {
			cout << "\nUpdate Client Info:\n";
			cout << "_________________________";
			_readClientInfo(client);

			clsBankClient::enSaveResults saveResults;

			saveResults = client.save();

			switch (saveResults)
			{
			case clsBankClient::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError account was not saved because it is Empty.";
				break;
			}
			case clsBankClient::enSaveResults::svSucceed:
			{
				cout << "\nAccout Added Successfully";
				_printClient(client);
				break;
			}
			case clsBankClient::enSaveResults::svFailedAccountNumberExists:
			{
				cout << "\nError account was not saved because it is already used.";
				break;
			}
			}

		}
	}
};

