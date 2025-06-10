#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
#include "clsUtil.h";
using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
	static void _printClientRecordBalanceLine(clsBankClient client) {

		cout << setw(25) << left << "" << "| " << left << setw(15) << client.getAccountNumber();
		cout << "| " << left << setw(40) << client.getPinCode();
		cout << "| " << left << setw(12) << client.getAccountBalance();

	}
public:
	static void showTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string subtitle = "\t" + to_string(vClients.size()) + " Client(s)";

		_drawScreenHeader("\t Total Balances Screen", subtitle);

		

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(25) << left << "" << "\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;


		if (vClients.size() == 0) {
			cout << "\t\t\tNo clients available in the system!!!!";
		}
		else {
			for (clsBankClient& c : vClients) {
				_printClientRecordBalanceLine(c);
				cout << endl;
			}
			cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
			cout << "__________________________\n" << endl;
		}
		double totalBalances = clsBankClient::getTotalBalances();
		cout <<setw(8) << left  << "" <<   "\t\t\tTotal Balance: " << totalBalances << endl;
		cout << setw(8) << left << "" << "\t\t\t(" << clsUtil::NumberToText(totalBalances) << ")\n\n";
	}
};

