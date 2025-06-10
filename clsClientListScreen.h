#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h";
#include "clsScreen.h";
using namespace std;

class clsClientListScreen : protected clsScreen
{

	static void _printClientRecord(clsBankClient c) {

		cout << setw(8) << left << "" << "| " << left << setw(15) << c.getAccountNumber();
		cout << "| " << left << setw(20) << c.getFullName();
		cout << "| " << left << setw(12) << c.getPhoneNumber();
		cout << "| " << left << setw(20) << c.getEmail();
		cout << "| " << left << setw(10) << c.getPinCode();
		cout << "| " << left << setw(12) << c.getAccountBalance();
	}
public:
	static void showClientList() {

		if (!checkAccessright(clsUser::enPermissions::pShowListClient))
		{
			return;
		}
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		

		string title = "\t Show Client List";
		string subtitle = "\t (" + to_string(vClients.size()) + ") Client(s)";

		_drawScreenHeader(title, subtitle);
		
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone Number";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vClients.size() == 0) {
			cout << "\t\t\tNo clients available in the system!!!!";
		}
		else {
			for (clsBankClient& c : vClients) {
				_printClientRecord(c);
				cout << endl;
			}
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "_________________________________________\n" << endl;
		}
	}
};

