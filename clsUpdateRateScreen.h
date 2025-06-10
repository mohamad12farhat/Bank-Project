#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateRateScreen : protected clsScreen
{
	static void _printCurrencyInfo(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "\n_________________________________";
		cout << "\nCountry   :" << Currency.getCountry();
		cout << "\nCode      :" << Currency.getCurrencyCode();
		cout << "\nName      :" << Currency.getCurrencyName();
		cout << "\nRate      :" << Currency.getRate();
		cout << "\n_________________________________\n";
	}

public:

	static void showUpdateCurrencyRateScreen()
	{
		_drawScreenHeader("Update Currency Screen");

		string code;
		cout << "Please enter currency code: ";
		code = clsInputValidate::ReadString();

		while (!clsCurrency::isCodeExist(code))
		{
			cout << "\n\nCode does not exist, please enter another one: ";
			code = clsInputValidate::ReadString();
		}

		clsCurrency currency = clsCurrency::findCurrencyByCode(code);

		_printCurrencyInfo(currency);

		char answer = 'y';
		cout << "\nAre you sure do you want to update this currency y/n?: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			cout << "\nUpdate Currency Rate:\n";
			cout << "\n____________________________\n\n";
			float rate = 0;
			cout << "\nPlease enter new rate: ";
			rate = clsInputValidate::ReadFloatNumber();
			currency.updateRate(rate);
			cout << "\n\nCurrency Rate updated successfully.\n";
			_printCurrencyInfo(currency);
		}
	}
};

