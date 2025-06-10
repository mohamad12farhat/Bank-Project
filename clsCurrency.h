#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class clsCurrency
{
	string _country;
	string _currencyCode;
	string _currencyName;
	float _rate;

	enum enMode { enEmpty = 0, enUpdate = 1 };
	enMode _mode;

	static clsCurrency _convertLineToCurrencyObject(string line, string separator = "#//#")
	{
		vector<string> vCurrencies = clsString::Split(line, separator);

		return clsCurrency(enMode::enUpdate, (vCurrencies[0]), vCurrencies[1], vCurrencies[2],
		   stof(vCurrencies[3]));
	}

	static clsCurrency _getCurrencyEmptyObject()
	{
		return clsCurrency(enMode::enEmpty, "", "", "", 0);
	}

	 string _convertCurrencyRecordToLine(clsCurrency currency, string separator = "#//#")
	{
		 string stCurrencyRecord = "";

		 stCurrencyRecord += currency.getCountry() + separator;
		 stCurrencyRecord += currency.getCurrencyCode() + separator;
		 stCurrencyRecord += currency.getCurrencyName() + separator;
		 stCurrencyRecord += to_string(currency.getRate());

		 return stCurrencyRecord;

	}

	 void _saveNewRateCurrency(vector<clsCurrency> vCurrencies)
	{
		fstream myFile;
		myFile.open("Currencies.txt", ios::out);

		if (myFile.is_open())
		{
			for (clsCurrency& c : vCurrencies)
			{
				string dataline = _convertCurrencyRecordToLine(c);
				myFile << dataline << endl;
				
			}
			myFile.close();
		}
		
	}

	static vector<clsCurrency> _loadCurrenciesDataFromFile()
	{
		fstream myFile;
		vector<clsCurrency> vCurrencies;
		myFile.open("Currencies.txt", ios::in);
		string line;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				vCurrencies.push_back(currency);
			}
			myFile.close();
		}

		return vCurrencies;
	}

	void _update()
	{
		vector<clsCurrency> vCurrencies = _loadCurrenciesDataFromFile();

		for (clsCurrency& c : vCurrencies)
		{
			if (c.getCurrencyCode() == getCurrencyCode())
			{
				c = *this;
				break;
			}
		}
		_saveNewRateCurrency(vCurrencies);
	}

public:
	
	
	clsCurrency(enMode mode, string country, string currencyCode, string currencyName,float rate)
	{
		_mode = mode;
		_country = country;
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_rate = rate;
	}


	string getCountry()
	{
		return _country;
	}

	string getCurrencyCode()
	{
		return _currencyCode;
	}

	string getCurrencyName()
	{
		return _currencyName;
	}

	void updateRate(float rate)
	{
		_rate = rate;
		_update();
	}

	float getRate()
	{
		return _rate;
	}

	bool isEmpty()
	{
		return (_mode == enMode::enEmpty);
	}

	static clsCurrency findCurrencyByCountry(string country)
	{
		country = clsString::UpperAllString(country);
		fstream myFile;
		myFile.open("Currencies.txt", ios::in);
		string line;

		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				if (clsString::UpperAllString(currency.getCountry()) == country)
				{
					myFile.close();
					return currency;
				}
			}
			
			myFile.close();
		}
		return _getCurrencyEmptyObject();
	}

	static clsCurrency findCurrencyByCode(string code)
	{
		code = clsString::UpperAllString(code);
		fstream myFile;
		myFile.open("Currencies.txt", ios::in);
		string line;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				clsCurrency user = _convertLineToCurrencyObject(line);
				if (user.getCurrencyCode() == code)
				{
					myFile.close();
					return user;
				}
					
			}
			myFile.close();
		}
		return _getCurrencyEmptyObject();
	}

	static bool isCodeExist(string code)
	{
		clsCurrency c = clsCurrency::findCurrencyByCode(code);
		return (!c.isEmpty());
	}

	static bool isCountryExist(string Country)
	{
		clsCurrency c = clsCurrency::findCurrencyByCountry(Country);
		return (!c.isEmpty());
	}

	static vector<clsCurrency> getCurrenciesList()
	{
		return _loadCurrenciesDataFromFile();
	}

	float convertCurrencyToUsd(float amount)
	{
		return amount / getRate();
	}

	float convertCurrencyFromUsdToAnotherCuurency(float amount, clsCurrency currency)
	{
		float amountInUsd = convertCurrencyToUsd(amount);

		if (currency.getCurrencyCode() == "USD")
		{
			return amountInUsd;
		}

		return amountInUsd * currency.getRate();
	}
};

