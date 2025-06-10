#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";

using namespace std;

class clsFindUserScreen : protected clsScreen
{
	static void _printUserInfo(clsUser user)
	{
		cout << "\n\nUser Card: ";
		cout << "\n_________________________";
		cout << "\nFirst Name         :" << user.FirstName;
		cout << "\nLast Name          :" << user.LastName;
		cout << "\nFull Name          :" << user.getFullName();
		cout << "\nEmail              :" << user.Email;
		cout << "\nPhone Number       :" << user.PhoneNumber;
		cout << "\nUsername           :" << user.Username;
		cout << "\nPassword           :" << user.Password;
		cout << "\nPermissions        :" << user.Permissions;
		cout << "\n_________________________";
	}

public:
	static void showFindUserScreen()
	{
		_drawScreenHeader("\t FindUserScreen");

		

		string username = "";

		cout << "\nPlease enter username: ";
		username = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(username))
		{
			cout << "\nUser does not exist, please enter another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(username);

		if (user.isEmpty())
		{
			cout << "\n\nUser was not found.\n";
		}
		else {
			cout << "\n\nUser found.\n";
		}

		_printUserInfo(user);
	}
};

