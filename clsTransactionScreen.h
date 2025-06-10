#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalancesScreen.h";
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>
using namespace std;
class clsTransactionScreen : protected clsScreen 
{
	enum _enTransactionMenueOption {enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, 
		enTransfer = 4, enTransferLog = 5, enMainMenue = 6};


	static short _readTransactionMenueOption()
	{
		
		short choice = 0;
		cout << "\t\t\t\t\tChoose what do you want to do [1 to 6]?: ";
		choice = clsInputValidate::ReadShortNumberBetween(1, 6);

		return choice;
	}

	static void _goBackToTransactionMenue() {

		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transaction Menue...\n";
		system("pause");
		showTransactionMenue();
	}

	static void _showDepositScreen() {
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen() {

		clsWithdrawScreen::showWithdrawScreen();
	}

	static void _showTotalBalancesScreen() {

		clsTotalBalancesScreen::showTotalBalances();
	}

	static void _showTransferScreen()
	{
		clsTransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen()
	{
		clsTransferLogScreen::showTransferLogScreen();
		
	}

	static void _performTransactionMenueOption(_enTransactionMenueOption option)
	{
		switch (option)
		{
		case _enTransactionMenueOption::enDeposit:
		{
			system("cls");
			_showDepositScreen();
			_goBackToTransactionMenue();
			break;
		}
		case _enTransactionMenueOption::enWithdraw:
		{
			system("cls");
			_showWithdrawScreen();
			_goBackToTransactionMenue();
			break;
		}
		case _enTransactionMenueOption::enTotalBalances:
		{
			system("cls");
			_showTotalBalancesScreen();
			_goBackToTransactionMenue();
			break;
		}
		case _enTransactionMenueOption::enTransfer:
		{
			system("cls");
			_showTransferScreen();
			_goBackToTransactionMenue();
		}
		case _enTransactionMenueOption::enTransferLog:
		{
			system("cls");
			_showTransferLogScreen();
			_goBackToTransactionMenue();
		}
		case _enTransactionMenueOption::enMainMenue:
		{
			// do nothing the main screen will handle it..
		}
		}
	}

public:
	static void showTransactionMenue() {

		system("cls");

		if (!checkAccessright(clsUser::enPermissions::pTransaction))
		{
			return;
		}
		_drawScreenHeader("\t Transaction Screen");

		

		cout << "\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t\t\tTransaction Menue\n";
		cout << "\n\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t  [1]Deposit." << endl;
		cout << "\t\t\t\t\t  [2]Withdraw." << endl;
		cout << "\t\t\t\t\t  [3]Total Balances." << endl;
		cout << "\t\t\t\t\t  [4]Transfer." << endl;
		cout << "\t\t\t\t\t  [5]Transfer Log." << endl;
		cout << "\t\t\t\t\t  [6]Main Menue." << endl;
		cout << "\t\t\t\t\t======================================\n";
		_performTransactionMenueOption(_enTransactionMenueOption(_readTransactionMenueOption()));
	}

};

