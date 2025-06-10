#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsClientListScreen.h";
#include "clsInputValidate.h";
#include "clsAddNewClientScreen.h";
#include "clsDeleteScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionScreen.h";
#include "clsManageUsersScreen.h";
#include "clsLoginRegisterScreen.h"
#include "clsCurrenciesExchangeScreen.h"
#include "Globall.h";
using namespace std;


class clsMainScreen : protected clsScreen
{
	enum _enMainMenueOptions {enShowClientList = 1, enAddClient = 2, enDeleteClient = 3, enUpdateClient = 4,
	enFindClient = 5, enTransactions = 6, enManageUsers = 7, enLoginRegister = 8,enCurrencies = 9, 
		enExit = 10};

	static short _readMainMenueOption() {
		short choice = 0;

		cout << "\t\t\t\t\tChoose what do you want to do? [1 to 10]: ";
		choice = clsInputValidate::ReadShortNumberBetween(1, 10);

		return choice;
	}

	static void _showClientsListScreen() {
		
		clsClientListScreen::showClientList();
	}

	static void _showAddClientScreen(){
		
		clsAddNewClientScreen::addNewClient();
	}

	static void _showDeleteClientScreen() {
		clsDeleteScreen::showDeleteClientScreen();
	}

	static void _showUpdateClientScreen() {
		
		clsUpdateClientScreen::showUpdateClientScreen();
	}

	static void _showFindClientScreen() {
		
		clsFindClientScreen::showFindClientScreen();
	}

	static void _showTransactionMenue() {
		
		clsTransactionScreen::showTransactionMenue();
	}

	static void _showManageUsersMenue() {
		
		clsManageUsersScreen::showManageUsersScreen();
	}

	static void _showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::showLoginRegisterScreen();
	}

	static void _showCurrencyScreen()
	{
		clsCurrenciesExchangeScreen::showCurrenciesScreen();
	}

	/*static void _showExitScreen() {
		cout << "\nExit Screen  will be here...\n";
	}*/

	static void _logout()
	{
		CurrentUser = clsUser::find("","");
	}

	static void _goBackToMainMenueScreen() {
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		showMainMenueScreen();
	}

	static void _performMainMenueOption(_enMainMenueOptions option)
	{
		switch (option)
		{
		case _enMainMenueOptions::enShowClientList:
		{
			system("cls");
			_showClientsListScreen();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enAddClient:
		{
			system("cls");
			_showAddClientScreen();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enDeleteClient:
		{
			system("cls");
			_showDeleteClientScreen();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enUpdateClient:
		{
			system("cls");
			_showUpdateClientScreen();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enFindClient:
		{
			system("cls");
			_showFindClientScreen();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enTransactions:
		{
			system("cls");
			_showTransactionMenue();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enManageUsers:
		{
			system("cls");
			_showManageUsersMenue();
			_goBackToMainMenueScreen();
			break;
		}
		case _enMainMenueOptions::enLoginRegister:
		{
			system("cls");
			_showLoginRegisterScreen();
			_goBackToMainMenueScreen();
		}
		case _enMainMenueOptions::enCurrencies:
		{
			system("cls");
			_showCurrencyScreen();
			_goBackToMainMenueScreen();
		}
		case _enMainMenueOptions::enExit:
		{
			system("cls");
			_logout();
			break;
		}
		}
	}

public:

	static void showMainMenueScreen() {
		system("cls");

		_drawScreenHeader("\t\tMain Screen");

		

		cout << "\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t\t\tMain Menue\n";
		cout << "\n\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t  [1]Show Client List." << endl;
		cout << "\t\t\t\t\t  [2]Add New Client." << endl;
		cout << "\t\t\t\t\t  [3]Delete Client." << endl;
		cout << "\t\t\t\t\t  [4]Update Client Info." << endl;
		cout << "\t\t\t\t\t  [5]Find Client." << endl;
		cout << "\t\t\t\t\t  [6]Transactions." << endl;
		cout << "\t\t\t\t\t  [7]Manage Users." << endl;
		cout << "\t\t\t\t\t  [8]Login Register." << endl;
		cout << "\t\t\t\t\t  [9]Currency Exchange." << endl;
		cout << "\t\t\t\t\t  [10]Logout." << endl;
		cout << "\t\t\t\t\t======================================\n";
		_performMainMenueOption(_enMainMenueOptions(_readMainMenueOption()));

	}
};

