#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

	static void _printLoginRegisterRecord(clsUser::stLoginRegisterRecord loginRegisterRecord)
	{
		cout << setw(8) << left << "" << "| " << left << setw(35) << loginRegisterRecord.dateAndTime;
		cout << "| " << left << setw(20) << loginRegisterRecord.username;
		cout << "| " << left << setw(20) << loginRegisterRecord.password;
		cout << "| " << left << setw(10) << loginRegisterRecord.permissions;
	}

public:
	static void showLoginRegisterScreen()
	{

		if (!checkAccessright(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}
		
		vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::getUserLoginRegisterData();

		string title = "\t Login Register List Screen";
		string subtitle = "\t" + to_string(vLoginRegisterRecord.size()) + " Record(s)";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;;

		if (vLoginRegisterRecord.size() == 0) {
			cout << "\t\t\tNo Logins available in the system!!!!";
		}
		else {
			for (clsUser::stLoginRegisterRecord l : vLoginRegisterRecord) {
				_printLoginRegisterRecord(l);
				cout << endl;
			}
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "_________________________________________\n" << endl;
		}
	}
};

