#pragma once
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include "Inventory.h"
#include "User.h"
class Server
{
private:
	string m_relativePath;
	const string m_str_storage = "storage.txt";

public:

	bool readUser(UserID uid, User& user) const;
	bool writeUser(User& user) const;

	bool writeStorage(Inventory& inventory) const;
	bool readStorage(Inventory& inventory) const;

	void setPath(string path);

public:
	bool buy(UserID uid, ItemID iid);
	void sell(UserID uid, ItemID iid);

	bool fetchUser(UserID uid, User& user) const;
	bool createUser(UserID uid);

	bool fetchStorage(Inventory& inventory) const;

	void clear();

	Server(string path = "./TESTING/");

};

