#pragma once
#include <iostream>
#include "clsPerson.h";
#include <fstream>
#include <vector>
#include "clsString.h";
#include "clsDate.h";
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
	enum _enMode { enEmpty = 0, enUpdate = 1,enAddNew = 2 };
	_enMode _mode;
	string _username;
	string _password;
	int _permissions;
	bool _markedForDelete = false;

	
	static clsUser _convertLineToUserObject(string line, string dilem = "#//#")
	{

		vector<string> vUsers = clsString::Split(line, dilem);


		return clsUser(_enMode::enUpdate, vUsers[0], vUsers[1], vUsers[2], vUsers[3], vUsers[4],
			clsUtil::DecryptText(vUsers[5],3),stoi(vUsers[6]));
	}

	static vector<clsUser> _loadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		string line;
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				clsUser user = _convertLineToUserObject(line);
				vUsers.push_back(user);
			}
			myFile.close();
			
		}
		return vUsers;
	}

	static clsUser _getEmptyUserObject()
	{
		return clsUser(_enMode::enEmpty, "", "","", "", "", "", 0);
	}

	string _convertUserObjectToLine(clsUser u,string separator = "#//#")
	{
		string userRecord = "";
		userRecord += u.FirstName + separator;
		userRecord += u.LastName + separator;
		userRecord += u.Email + separator;
		userRecord += u.PhoneNumber + separator;
		userRecord += u.Username + separator;
		userRecord += clsUtil::EncryptText(u.Password, 3) + separator;
		userRecord += to_string(u.Permissions);

		return userRecord;
		
	}

	void _saveUserDataToFile(vector<clsUser> vUsers)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);

		if (myFile.is_open())
		{
			for (clsUser& u : vUsers)
			{
				if (u.markedForDeleted() == false)
				{
					string dataLine = _convertUserObjectToLine(u);
					myFile << dataLine << endl;
				}
				
			}
			myFile.close();
		}
	}

	void _update()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& u : vUsers)
		{
			if (u.Username == Username)
			{
				u = *this;
				break;
			}
		}
		_saveUserDataToFile(vUsers);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream myFile;

		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	void _addNewUser()
	{
		_addDataLineToFile(_convertUserObjectToLine(*this));
	}

	string _prepareLoginRecord(string separator = "#//#")
	{
		string loginRecord = "";
		loginRecord += clsDate::getSystemDateTimeString() + separator;
		loginRecord += Username + separator;
		loginRecord += clsUtil::EncryptText(Password,3) + separator;
		loginRecord += to_string(Permissions);

		return loginRecord;
	}

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _convertLoginRegisterLineToRecord(string line, string separator = "#//#")
	{
		vector<string> vLoginRegisterRecord = clsString::Split(line, separator);

		
		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.dateAndTime = vLoginRegisterRecord[0];
		LoginRegisterRecord.username = vLoginRegisterRecord[1];
		LoginRegisterRecord.password = clsUtil::DecryptText(vLoginRegisterRecord[2],3);
		LoginRegisterRecord.permissions = stoi(vLoginRegisterRecord[3]);


		return LoginRegisterRecord;

	}

public:

	static struct stLoginRegisterRecord
	{
		string dateAndTime;
		string username;
		string password;
		int permissions;
	};

	enum enPermissions {enAll = -1, pShowListClient = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
	pFindClient = 16, pTransaction = 32, pManageUsers = 64, pLoginRegister = 128};

	clsUser(_enMode mode, string firstName, string lastName, string email, string phoneNumber,
		string username, string password, int permissions)
		:clsPerson(firstName, lastName, email, phoneNumber)
	{
		_mode = mode;
		_username = username;
		_password = password;
		_permissions = permissions;
	}

	void setUsername(string username)
	{
		_username = username;
	}

	string getUsername()
	{
		return _username;
	}

	__declspec(property(get = getUsername, put = setUsername)) string Username;

	void setPassword(string password)
	{
		_password = password;
	}

	string getPassword()
	{
		return _password;
	}

	__declspec(property(get = getPassword, put = setPassword )) string Password;

	void setPermissions(int permissions)
	{
		_permissions = permissions;
	}

	int getPermissions()
	{
		return _permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	bool markedForDeleted()
	{
		return _markedForDelete;
	}

	static clsUser find(string username)
	{

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsUser user = _convertLineToUserObject(line);

				if (user.getUsername() == username)
				{
					myFile.close();
					return user;
				}
			}
			

			
			myFile.close();
		}
		return _getEmptyUserObject();
	}

	static clsUser find(string username, string password)
	{

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsUser user = _convertLineToUserObject(line);

				if (user.Username == username && user.Password == password)
				{
					myFile.close();
					return user;
				}
			}
			myFile.close();
		}
		return _getEmptyUserObject();
	}

	bool isEmpty()
	{
		return (_mode == _enMode::enEmpty);
	}

	static bool isUserExist(string username)
	{
		clsUser user = clsUser::find(username);
		return (!user.isEmpty());
	}

	static clsUser getAddNewUserObject(string username)
	{
		return clsUser(_enMode::enAddNew, "", "", "", "", username, "", 0);
	}

	enum enSaveResult {svEmptyFailedObject = 1, svSucceed = 2, svFailedUserExist = 3};

	enSaveResult save()
	{
		switch(_mode)
		{
		case _enMode::enEmpty:
		{
			if(isEmpty())
				return enSaveResult::svEmptyFailedObject;
		}
		case _enMode::enUpdate:
		{
			_update();
			return enSaveResult::svSucceed;
		}
		case _enMode::enAddNew:
		{
			if (isUserExist(Username))
			{
				return enSaveResult::svFailedUserExist;
			}
			else
			{
				_addNewUser();
				_mode = _enMode::enUpdate;
				return enSaveResult::svSucceed;
			}
		}
		}
		
	}

	bool deleteUser()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& u : vUsers)
		{
			if (u.Username == _username)
			{
				u._markedForDelete = true;
				break;
			}
		}

		_saveUserDataToFile(vUsers);
		*this = _getEmptyUserObject();
		return true;
	}
	

	static vector<clsUser> getUserLists()
	{
		return _loadUsersDataFromFile();
	}

	bool checkAccessPermissions(enPermissions permissions)
	{
		if (this->Permissions == enPermissions::enAll)
			return true;

		if ((permissions & this->Permissions) == permissions)
			return true;
		else 
			return false;
		
		
	}

	void registerLogin()
	{
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::out | ios::app);

		string dataLine = _prepareLoginRecord();

		if (myFile.is_open())
		{
			myFile << dataLine << endl;

			myFile.close();
		}
	}

	static vector<stLoginRegisterRecord> getUserLoginRegisterData()
	{
		fstream myFile;

		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		myFile.open("LoginRegister.txt", ios::in);
		string line;
		
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				stLoginRegisterRecord LoginRegisterRecord = _convertLoginRegisterLineToRecord(line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
		}

		return vLoginRegisterRecord;
	}

};

