#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{

	static void _printTransferLogRecord(clsBankClient::stTransferLog transferLog)
	{
		cout << setw(8) << left << "" << "| " << setw(35) << left << transferLog.dateAndTime;
		cout << "| " << setw(10) << left << transferLog.sourceAccount;
		cout << "| " << setw(10) << left << transferLog.destinationAccount;
		cout << "| " << setw(12) << left << transferLog.amount;
		cout << "| " << setw(12) << left << transferLog.newAmountForSource;
		cout << "| " << setw(12) << left << transferLog.newAmountForDestination;
		cout << "| " << setw(15) << left << transferLog.sourceUsername;
	}

public:

	static void showTransferLogScreen()
	{
		vector<clsBankClient::stTransferLog> vTransferLog = clsBankClient::getTransferLogList();

		string title = "\t Transfer Log List Screen";
		string subtitle = "\t(" + to_string(vTransferLog.size()) + ") Record(s)";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "________________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << setw(35) << left << "Date/Time";
		cout << "| " << setw(10) << left << "s.Acc";
		cout << "| " << setw(10) << left << "d.Acc";
		cout << "| " << setw(12) << left << "Amount";
		cout << "|" << setw(12) << left << "s.Balance";
		cout << "| " << setw(12) << left << "d.Balance";
		cout << "| " << setw(15) << left << "User";


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________________\n" << endl;

		if (vTransferLog.size() == 0)
		{
			cout << "\n\n\t\tNo Transfer Log list is done.\n";
		}

		for (clsBankClient::stTransferLog t : vTransferLog)
		{
			_printTransferLogRecord(t);
			cout << endl;
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________________\n" << endl;
	}
};

