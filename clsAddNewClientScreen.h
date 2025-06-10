#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsInputValidate.h";

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

	static void _readClientInfo(clsBankClient& client) {


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

	static void addNewClient() 
	{

		if (!checkAccessright(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}
		_drawScreenHeader("\t Add New Client Screen");
		
		string accountNumber = "";
		cout << "\nPlease enter account number: ";
		accountNumber = clsInputValidate::ReadString();
		
		while (clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount number is already used, choose another one: ";
			accountNumber = clsInputValidate::ReadString();
		}
		clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber);

		_readClientInfo(newClient);
		
		clsBankClient::enSaveResults saveResults;

		saveResults = newClient.save();

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
			_printClient(newClient);
			break;
		}
		case clsBankClient::enSaveResults::svFailedAccountNumberExists:
		{
			cout << "\nError account was not saved because it is already used.";
			break;
		}
		}


	}
};

