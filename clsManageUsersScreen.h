#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsListUserScreen.h";
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";
using namespace std;

class clsManageUsersScreen : protected clsScreen
{
	enum enManageUsersOption {enListUsers = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4,
	enFindUser = 5, enMainMenue = 6};

	static short _readManageUserOption()
	{
		short choice = 0;
		cout << "\t\t\t\t\tChoose what do you want to do [1 to 6]?: ";
		choice = clsInputValidate::ReadShortNumberBetween(1,6);

		return choice;
	}

	static void _goBackToManageUsersScreen()
	{
		cout << "\n\nPress any key to go back to Manage Users Screen...";

		system("pause");
		showManageUsersScreen();
	}

	static void _showUsersListScreen()
	{
		clsListUserScreen::showListUserScreen();
	}

	static void _showAddNewUserScreen()
	{
		clsAddNewUserScreen::showAddNewUserScreen();
	}

	static void _showDeleteUserScreen()
	{
		clsDeleteUserScreen::showDeleteUserScreen();
	}


	static void _showUpdateUserScreen()
	{
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _showFindUserScreen()
	{
		clsFindUserScreen::showFindUserScreen();
	}

	static void _performManageUserOption(enManageUsersOption option)
	{
		switch (option)
		{
		case enManageUsersOption::enListUsers:
		{
			system("cls");
			_showUsersListScreen();
			_goBackToManageUsersScreen();
			break;
		}
		case enManageUsersOption::enAddNewUser:
		{
			system("cls");
			_showAddNewUserScreen();
			_goBackToManageUsersScreen();
			break;
		}
		case enManageUsersOption::enDeleteUser:
		{
			system("cls");
			_showDeleteUserScreen();
			_goBackToManageUsersScreen();
			break;
		}
		case enManageUsersOption::enUpdateUser:
		{
			system("cls");
			_showUpdateUserScreen();
			_goBackToManageUsersScreen();
			break;
		}
		case enManageUsersOption::enFindUser:
		{
			system("cls");
			_showFindUserScreen();
			_goBackToManageUsersScreen();
			break;
		}
		case enManageUsersOption::enMainMenue:
		{
			// do nothing the main menue screen will handle it
		}
		}
	}

public:

	static void showManageUsersScreen() 
	{
		system("cls");

		if (!checkAccessright(clsUser::enPermissions::pManageUsers))
		{
			return;
		}
		_drawScreenHeader("\t Manage Users Screen");

		

		cout << "\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t\t\tManage Users Menue\n";
		cout << "\n\t\t\t\t\t======================================\n";
		cout << "\t\t\t\t\t  [1]List Users." << endl;
		cout << "\t\t\t\t\t  [2]Add New User." << endl;
		cout << "\t\t\t\t\t  [3]-Delete User." << endl;
		cout << "\t\t\t\t\t  [4]-Update User Info." << endl;
		cout << "\t\t\t\t\t  [5]-Find User." << endl;
		cout << "\t\t\t\t\t  [6]-Main Menue." << endl;
		cout << "\t\t\t\t\t======================================\n";
		_performManageUserOption(enManageUsersOption(_readManageUserOption()));
	}
};

