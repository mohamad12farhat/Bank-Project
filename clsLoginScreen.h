#pragma once
#include <iostream>
#include "clsUser.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsMainScreen.h";
#include <fstream>
#include "Globall.h";

using namespace std;

class clsLoginScreen : protected clsScreen
{
	static bool _login()
	{
		bool loginFailed = false;

		short loginFailedCount = 0;
		string username, password;

		do {
			if (loginFailed)
			{
				loginFailedCount++;
				cout << "\nInvalid Username or Password!!!";
				cout << "\nYou have " << 3- loginFailedCount << " trial (s) left.\n";
			}

			if (loginFailedCount == 3)
			{
				cout << "\n\nYou are locked after 3 trials trails.\n";
				return false;
			}

			cout << "\nEnter username: ";
			username = clsInputValidate::ReadString();

			cout << "\nEnter password: ";
			password = clsInputValidate::ReadString();

			CurrentUser = clsUser::find(username, password);

			loginFailed = CurrentUser.isEmpty();

		} while (loginFailed);
	
		CurrentUser.registerLogin();
		clsMainScreen::showMainMenueScreen();
		return true;

	}

	

	

public:

	static bool showLoginScreen()
	{
		system("cls");
		_drawScreenHeader("\t Login Screen");

		return _login();
		
	}
};

