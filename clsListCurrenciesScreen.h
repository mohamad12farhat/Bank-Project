#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include <vector>
using namespace std;

class clsListCurrenciesScreen : protected clsScreen 
{
	static void printCurrenciesRecord(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.getCountry();
		cout << "| " << setw(8) << left << Currency.getCurrencyCode();
		cout << "| " << setw(45) << left << Currency.getCurrencyName();
		cout << "| " << setw(10) << left << Currency.getRate();
	}

public:

	static void showListCurrenciesScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();

		string title = "\t Currencies List Screen.";
		string subtitle = "\t (" + to_string(vCurrencies.size()) + ") Currency(ies).";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left <<  setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\n\t No Currencies available in the system!!!!\n\n";
		}
		else 
		for (clsCurrency& c : vCurrencies)
		{
			printCurrenciesRecord(c);
			cout << endl;
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;
	}
};

