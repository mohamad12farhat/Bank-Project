#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h";

using namespace std;

class clsCurrenciesExchangeScreen : protected clsScreen
{
	enum enCurrenciesExchangeOption {enListCurrencies = 1, enFindCurrencies = 2, 
		enUpdateRate = 3, enCurrencyCalculator = 4, enMainMenue = 5};


	static short _readCurrencyMenueOption()
	{
		short choice = 0;
		cout << "\t\t\t\t\tChoose what do you want to do? [1 to 5]?: ";
		choice = clsInputValidate::ReadDblNumberBetween(1, 5);

		return choice;
	}

	static void _showListCurrenciesScreen()
	{
		clsListCurrenciesScreen::showListCurrenciesScreen();
	}
	
	static void _showFindCurrenciesScreen()
	{
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _showUpdateRateCurrenciesScreen()
	{
		clsUpdateRateScreen::showUpdateCurrencyRateScreen();
	}

	static void _showCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _goBackToCurrenciesExchangeScreen()
	{
		cout << "\nPlease preen any key to go back to Currencies Exchange Screen.\n";

		system("pause");
		showCurrenciesScreen();
	}

	static void _performCurrenCiesExchangeOption(enCurrenciesExchangeOption option)
	{
		switch (option)
		{
		case enCurrenciesExchangeOption::enListCurrencies:
		{
			system("cls");
			_showListCurrenciesScreen();
			_goBackToCurrenciesExchangeScreen();
			break;
		}
		case enCurrenciesExchangeOption::enFindCurrencies:
		{
			system("cls");
			_showFindCurrenciesScreen();
			_goBackToCurrenciesExchangeScreen();
			break;
		}
		case enCurrenciesExchangeOption::enUpdateRate:
		{
			system("cls");
			_showUpdateRateCurrenciesScreen();
			_goBackToCurrenciesExchangeScreen();
			break;
		}
		case enCurrenciesExchangeOption::enCurrencyCalculator:
		{
			system("cls");
			_showCurrencyCalculatorScreen();
			_goBackToCurrenciesExchangeScreen();
			break;
		}
		case enCurrenciesExchangeOption::enMainMenue:
		{
			// do nothing
		}
		}
	}


public:

	static void showCurrenciesScreen()
	{
		system("cls");
		_drawScreenHeader("\t Currency Exchange Main Screen");
		
		cout << "\t\t\t\t\t==============================================\n";
		cout << "\t\t\t\t\t\tCurrency Exchange Menue\n";
		cout << "\n\t\t\t\t\t==============================================\n";
		cout << "\t\t\t\t\t  [1]List Currencies." << endl;
		cout << "\t\t\t\t\t  [2]Find Currency." << endl;
		cout << "\t\t\t\t\t  [3]Update Rate." << endl;
		cout << "\t\t\t\t\t  [4]Currency Calculator." << endl;
		cout << "\t\t\t\t\t  [5]Main Menue." << endl;
		cout << "\t\t\t\t\t==============================================\n";
		_performCurrenCiesExchangeOption(enCurrenciesExchangeOption(_readCurrencyMenueOption()));
	}
	
};

