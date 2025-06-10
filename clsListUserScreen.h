#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include <iomanip>
using namespace std;


class clsListUserScreen : protected clsScreen
{
	static void _printClientRecord(clsUser u) {

		cout << setw(8) << left << "" << "| " << left << setw(15) <<u.Username;
		cout << "| " << left << setw(25) << u.getFullName();
		cout << "| " << left << setw(12) << u.PhoneNumber;
		cout << "| " << left << setw(20) << u.Email;
		cout << "| " << left << setw(10) << u.Password;
		cout << "| " << left << setw(12) << u.Permissions;
	}
public:

	static void showListUserScreen()
	{

		vector<clsUser> vUsers  = clsUser::getUserLists();

		

		string title = "\t Show Users List";
		string subtitle = "\t (" + to_string(vUsers.size()) + ") User(s)";

		_drawScreenHeader(title, subtitle);

		

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Username";
		cout << "| " << left << setw(25) << "FullName";
		cout << "| " << left << setw(12) << "Phone Number";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

		if (vUsers.size() == 0) {
			cout << "\t\t\tNo Users available in the system!!!!";
		}
		else {
			for (clsUser& u : vUsers) {
				_printClientRecord(u);
				cout << endl;
			}
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "___________________________________________________\n" << endl;
		}
	}
};

