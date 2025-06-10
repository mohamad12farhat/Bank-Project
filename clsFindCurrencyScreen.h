#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
	enum enOptions {enCode = 1, enCountry = 2};

	static string readCurrencyCode()
	{
		string code;
		cout << "\n\nPlease enter currency code: ";
		code = clsInputValidate::ReadString();

		while (!clsCurrency::isCodeExist(code))
		{
			cout << "\nCode is not found. Please enter another one: ";
			code = clsInputValidate::ReadString();
		}

		return code;
	}

	static string readCountry()
	{
		string country;
		cout << "\n\nPlease enter country name: ";
		country = clsInputValidate::ReadString();

		while (!clsCurrency::isCountryExist(country))
		{
			cout << "\nCountry is not found. Please enter another one: ";
			country = clsInputValidate::ReadString();
		}

		return country;
	}

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

	static void showFindCurrencyScreen()
	{
		_drawScreenHeader("\t Find Currency Screen");

		short answer = 0;
		cout << "\nFind By [1]: Code or [2] Country ?: ";
		answer = clsInputValidate::ReadShortNumberBetween(1,2);

		
		switch (answer)
		{
		case enOptions::enCode:
		{
			string code = readCurrencyCode();
			clsCurrency currency = clsCurrency::findCurrencyByCode(code);
			_printCurrencyInfo(currency);
			break;
		}
		case enOptions::enCountry:
		{
			string country = readCountry();
			clsCurrency currency = clsCurrency::findCurrencyByCountry(country);
			_printCurrencyInfo(currency);
			break;
		}
		}
		cout << "\nCurrency Found:\n";
		
	}
};

