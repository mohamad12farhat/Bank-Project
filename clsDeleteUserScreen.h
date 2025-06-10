#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";

using namespace std;
class clsDeleteUserScreen : protected clsScreen
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
	static void showDeleteUserScreen()
	{

		_drawScreenHeader("\t Delete User Screen");

		

		string username = "";

		cout << "\nPlease enter username: ";
		username = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(username))
		{
			cout << "\n\nUsername does not exist. Please enter another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(username);

		_printUserInfo(user);

		char answer = 'y';
		cout << "\n\nAre you sure do you want to delete this user?(y for yes and n for no)?: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			if (user.deleteUser())
			{
				cout << "\n\nUser deleted Successfully.\n";
				_printUserInfo(user);

			}
			else
			{
				cout << "\n\nError, user was not deleted.\n";
			}
		}
	}
};

