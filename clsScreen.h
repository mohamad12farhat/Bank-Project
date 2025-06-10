#pragma once
#include <iostream>
#include "clsUser.h"
#include "Globall.h"
#include "clsDate.h"
using namespace std;
class clsScreen
{

protected:
	static void _drawScreenHeader(string title,string subTitle ="")
	{
		cout << "\t\t\t\t\t_________________________________________\n\n";
		cout << "\t\t\t\t\t" << title << endl;
		if (subTitle != "") {
			cout << "\n\t\t\t\t\t" << subTitle << endl;
		}
		cout << "\n\t\t\t\t\t_________________________________________\n\n";

		cout << "\n\t\t\t\t\tUser: " << CurrentUser.Username;
		cout << "\n\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << endl;

	 }

	static bool checkAccessright(clsUser::enPermissions permissions)
	{
		if (!CurrentUser.checkAccessPermissions(permissions))
		{
			cout << "\t\t\t\t\t________________________________________";
			cout << "\n\n\t\t\t\t\tAccess Denied! Contact your Admin!!!!!";
			cout << "\n\t\t\t\t\t________________________________________\n";
			return false;
		}
		else
		{
			return true;
		}
	}

	static void _addUserAndDateToScreen()
	{
		cout << "\n\t\t\t\t\tUser: " << CurrentUser.Username;
		clsDate date = clsDate::GetSystemDate();
		cout << "\n\t\t\t\t\tDate: " << date.Day << "/" << date.Month << "/" << date.Year << endl;
	}
};

