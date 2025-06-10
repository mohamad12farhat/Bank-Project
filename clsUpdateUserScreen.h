#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
	static int _readPermissionsToSet()
	{
		char answer = 'y';
		int permissions = 0;

		cout << "\nDo you want to give him full access? (y for yes and n for no)?: ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			return permissions = clsUser::enPermissions::enAll;
		}

		cout << "\nDo you want to give access to: \n";

		cout << "\nShow User List (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pShowListClient;
		}

		cout << "\nAdd New User (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete User (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate User (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nTransactions (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pTransaction;
		}

		cout << "\nManage Users (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nLogin Register (y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			permissions += clsUser::enPermissions::pLoginRegister;
		}

		return permissions;
	}

	static void _readUserInfo(clsUser& user)
	{


		cout << "\nEnter First Name: ";
		user.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		user.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		user.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone Number: ";
		user.PhoneNumber = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		user.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		user.Permissions = _readPermissionsToSet();

	}

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
	static void showUpdateUserScreen()
	{
		_drawScreenHeader("\t Update User Screen");


		string username = "";

		cout << "\nPlease enter username: ";
		username = clsInputValidate::ReadString();

		while (!clsUser::isUserExist(username))
		{
			cout << "\nUser does not exist, please enter another one: ";
			username = clsInputValidate::ReadString();
		}

		clsUser user = clsUser::find(username);

		_printUserInfo(user);

		char answer = 'y';
		cout << "\n\nAre you sure do you want to update this user?(y for yes and n for no)?: ";
		cin >> answer;


		if (tolower(answer) == 'y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________________";

			_readUserInfo(user);

			clsUser::enSaveResult saveResult = user.save();

			switch (saveResult)
			{
			case clsUser::enSaveResult::svEmptyFailedObject:
			{
				cout << "\n\nError, User was not saved because it's empty.\n";
				break;
			}
			case clsUser::enSaveResult::svFailedUserExist:
			{
				cout << "\n\nError, User was not saved because it's already used.\n";
				break;
			}
			case clsUser::enSaveResult::svSucceed:
			{
				cout << "\n\nUser Updated Successfully..\n";
				_printUserInfo(user);
				break;
			}
			}
		}


	}
};

