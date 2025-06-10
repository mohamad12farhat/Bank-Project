#pragma once
#include <iostream>
#include <string>
#include "clsString.h";
#include <fstream>
#include <vector>
#include "clsPerson.h";
#include "clsDate.h";
using namespace std;


class clsBankClient : public clsPerson
{
	enum enMode {enEmptyMode = 0, enUpdateMode = 1, enAddNew = 2};
	enMode _mode;

	string _accountNumber;
	string _pinCode;
	float _accountBalance;
	bool _markedForDelete = false;

	static clsBankClient _convertLineToClientObject(string line,string separator = "#//#") {
		vector<string> vClients;
		vClients = clsString::Split(line, separator);

		return clsBankClient(enMode::enUpdateMode,vClients[0],vClients[1], vClients[2], vClients[3],
			vClients[4],vClients[5],stoi(vClients[6]));
	}

	string _prepareTransferLogRecord(double amount, clsBankClient destinationClient,string username,string separator = "#//#")
	{
		string transferLog = "";

		transferLog += clsDate::getSystemDateTimeString() + separator;
		transferLog += _accountNumber + separator;
		transferLog += destinationClient._accountNumber + separator;
		transferLog += to_string(amount) + separator;
		transferLog += to_string(AccountBalance) + separator;
		transferLog += to_string(destinationClient.AccountBalance) + separator;
		transferLog += username;

		return transferLog;
	}

	void _registerTransferLog(double amount, clsBankClient destinationClient, string username)
	{

		string dataline = _prepareTransferLogRecord(amount, destinationClient,username);

		fstream myFile;
		myFile.open("TransferLog.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataline << endl;
			myFile.close();
		}
	}

	struct stTransferLog;
	
	static stTransferLog _convertTransferLogLineToRecord(string line, string separator = "#//#")
	{
		vector<string> vTransferLog = clsString::Split(line, separator);
		stTransferLog transferLogRecord;
		

		transferLogRecord.dateAndTime = vTransferLog[0];
		transferLogRecord.sourceAccount = vTransferLog[1];
		transferLogRecord.destinationAccount = vTransferLog[2];
		transferLogRecord.amount = stof(vTransferLog[3]);
		transferLogRecord.newAmountForSource = stof(vTransferLog[4]);
		transferLogRecord.newAmountForDestination = stof(vTransferLog[5]);
		transferLogRecord.sourceUsername = vTransferLog[6];

		return transferLogRecord;
	}


	static clsBankClient _getEmptyClientObject() {
		return clsBankClient(enMode::enEmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _loadClientDataFromFile() {
		fstream myFile;
		vector<clsBankClient> vClients;
		myFile.open("Clients.txt", ios::in);
		string line;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}
			myFile.close();
		}
		return vClients;
	}

	static string _convertClientObjectToLine(clsBankClient c, string dilem = "#//#") {
		string stClientRecord = "";

		stClientRecord += c.FirstName + dilem;
		stClientRecord += c.LastName + dilem;
		stClientRecord += c.Email + dilem;
		stClientRecord += c.PhoneNumber + dilem;
		stClientRecord += c.getAccountNumber() + dilem;
		stClientRecord += c.PinCode + dilem;
		stClientRecord += to_string(c.AccountBalance);


		return stClientRecord;
	}

	static void _saveClientDataToFile(vector<clsBankClient> vClients) {
		fstream myFile;
		myFile.open("Clients.txt", ios::out);

		if (myFile.is_open())
		{
			for (clsBankClient& c : vClients)
			{
				if (c._markedForDelete == false)
				{
					string dataLine = _convertClientObjectToLine(c);
					myFile << dataLine << endl;
				}
				

			}
			
			myFile.close();
		}
	}

	void _update() {
		vector<clsBankClient> _vClients = _loadClientDataFromFile();

		for (clsBankClient& c : _vClients) {
			if (c.getAccountNumber() == getAccountNumber()) {
				c = *this;
				break;
			}
		}

		_saveClientDataToFile(_vClients);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	void _addNewClient() {
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

public:


	struct stTransferLog
	{
		string dateAndTime;
		string sourceAccount;
		string destinationAccount;
		float amount;
		float newAmountForSource;
		float newAmountForDestination;
		string sourceUsername;
	};

	clsBankClient(enMode mode, string firstName, string lastName, string email, string phoneNumber, string accountNumber,string pinCode, float accountBalance)
	: clsPerson(firstName, lastName, email, phoneNumber)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;
	}

	string getAccountNumber() {
		return _accountNumber;
	}

	void setPinCode(string pinCode) {
		_pinCode = pinCode;
	}

	string getPinCode() {
		return _pinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float accountBalance) {
		_accountBalance = accountBalance;
	}

	float getAccountBalance() {
		return _accountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	

	bool getMarkedForDelete() {
		return _markedForDelete;
	}

	/*void print() {
		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "First Name       :" << getFirstName() << endl;
		cout << "Last Name        :" << getLastName() << endl;
		cout << "Full Name        :" << getFullName() << endl;
		cout << "Email            :" << getEmail() << endl;
		cout << "Phone Number     :" << getPhoneNumber() << endl;
		cout << "Account Number   :" << getAccountNumber() << endl;
		cout << "Pin Code         :" << getPinCode() << endl;
		cout << "Account Balance  :" << getAccountBalance() << endl;
		cout << "\n___________________\n";
	}*/
	
	 bool isEmpty() {
		return (_mode == enMode::enEmptyMode);
	}

	static clsBankClient find(string accountNumber) {
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

	

		string line;

		if (myFile.is_open()) {
		while (getline(myFile, line)) {

			clsBankClient client = _convertLineToClientObject(line);

			if (client.getAccountNumber() == accountNumber) {
				myFile.close();
				return client;
			}
			
		}
		myFile.close();
		}
		return _getEmptyClientObject();
	}

	static clsBankClient find(string accountNumber, string pinCode) {
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		string line;
		if (myFile.is_open()) {
			while (getline(myFile, line)) {
				clsBankClient client = _convertLineToClientObject(line);

				if (client.getAccountNumber() == accountNumber && client.getPinCode() == pinCode) {
					myFile.close();
					return client;
				}
			}
			myFile.close();
		}

		return _getEmptyClientObject();
	}

	enum enSaveResults {svFailedEmptyObject = 0, svSucceed = 1, svFailedAccountNumberExists = 2 };

	enSaveResults save() {
		switch (_mode)
		{
		case enMode::enEmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}
		case enMode::enUpdateMode: 
		{
			_update();
			return enSaveResults::svSucceed;
		}

		case enMode::enAddNew:
			if (clsBankClient::isClientExist(_accountNumber))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else {
				_addNewClient();
				_mode = enMode::enAddNew;
				return enSaveResults::svSucceed;
			}
			
		}
	}

	static bool isClientExist(string accountNumber) {

		clsBankClient client = clsBankClient::find(accountNumber);
		return (!client.isEmpty());

	}

	static clsBankClient getAddNewClientObject(string accountNumber) {
		return clsBankClient(enMode::enAddNew, "", "", "", "", accountNumber, "", 0);
	}

	bool  deleteClient() {
		vector<clsBankClient> vClients = _loadClientDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.getAccountNumber() == getAccountNumber()) {
				c._markedForDelete = true;
				break;
			}
		}

		_saveClientDataToFile(vClients);

		*this = _getEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> getClientsList() {
		return _loadClientDataFromFile();
	}

	static double getTotalBalances() {
		double totalBalance = 0;
		vector<clsBankClient> vClients = _loadClientDataFromFile();

		for (clsBankClient& c : vClients) {
			totalBalance += c.getAccountBalance();
		}

		return totalBalance;
	}

	void deposit(double amount)
	{
		_accountBalance += amount;
		save();
	}

	bool withdraw(double amount)
	{
		if (amount > _accountBalance)
		{
			return false;
		}
		else
		{
			_accountBalance -= amount;
			save();
			return true;
		}
		
	}

	bool transfer(float amount, clsBankClient& clientDestination,string username)
	{
		if (amount > AccountBalance)
		{
			return false;
		}
		withdraw(amount);
		clientDestination.deposit(amount);
		_registerTransferLog(amount, clientDestination,username);

		return true;
	}

	static vector<stTransferLog> getTransferLogList()
	{
		vector<stTransferLog> vTransferLog;

		fstream myFile;

		myFile.open("TransferLog.txt", ios::in);
		string line;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				stTransferLog transferLogRecord = _convertTransferLogLineToRecord(line);
				vTransferLog.push_back(transferLogRecord);
			}
			myFile.close();
		}
		return vTransferLog;
	}
};
	


