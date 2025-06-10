#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
	static void _printCurrencyCard(clsCurrency Currency,string title)
	{
		cout << "\n" << title << endl;
		cout << "\n_________________________________";
		cout << "\nCountry   :" << Currency.getCountry();
		cout << "\nCode      :" << Currency.getCurrencyCode();
		cout << "\nName      :" << Currency.getCurrencyName();
		cout << "\nRate      :" << Currency.getRate();
		cout << "\n_________________________________\n";
	}

	static float _readAmount()
	{
		float amount = 0.0;
		cout << "\n\nPlease enter amount to exchange: ";
		amount = clsInputValidate::ReadFloatNumber();

		return amount;
	}

	static clsCurrency _getCurrency(string message)
	{
		string currencyCode;
		cout << message << endl;

		currencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCodeExist(currencyCode))
		{
			cout << "\n\nCode does not exist. Please enter another one: ";
			currencyCode = clsInputValidate::ReadString();
		}

		clsCurrency currency = clsCurrency::findCurrencyByCode(currencyCode);

		return currency;
	}

	static void _printCalculationResults(float amount, clsCurrency currency1, clsCurrency currency2)
	{
		_printCurrencyCard(currency1, "Convert From");

		float amountInUsd = currency1.convertCurrencyToUsd(amount);

		cout << amount << " " << currency1.getCurrencyCode() << " = " << amountInUsd << " USD" << endl;

		if (currency2.getCurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting From Usd to:\n";
		_printCurrencyCard(currency2, "To: ");

		float amountInCurrency2 = currency1.convertCurrencyFromUsdToAnotherCuurency(amount, currency2);

		cout << amount << " " << currency1.getCurrencyCode() << " = " << amountInCurrency2 << " " <<
			currency2.getCurrencyCode() << endl;
	}

public:

	static void showCurrencyCalculatorScreen()
	{
		char Continue = 'y';
		do {
			system("cls");

			_drawScreenHeader("\t Currency Calculator Screen");

			clsCurrency currencyFrom = _getCurrency("\nPlease enter Currency1 Code: ");
			clsCurrency currencyTo = _getCurrency("\nPlease enter Currency2 Code: ");
			float amount = _readAmount();

			_printCalculationResults(amount, currencyFrom, currencyTo);

			cout << "\nDo you want to perform another calculation y/n?:";
			cin >> Continue;
		} while (tolower(Continue) == 'y');
		
	}
};

