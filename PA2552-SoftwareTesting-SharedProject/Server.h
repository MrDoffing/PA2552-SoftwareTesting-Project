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

	bool readUser(UserID uid, User& user) const;
	bool writeUser(User& user) const;

	bool writeStorage(Inventory& inventory) const;
	bool readStorage(Inventory& inventory) const;

	void setPath(string path);

public:
	bool createItemForStorage(Item& item) const; // should exist but needed for testing
	bool createItemForUser(UserID uid, Item& item) const;
	bool buy(UserID uid, ItemID iid) const;
	bool sell(UserID uid, ItemID iid) const;

	bool fetchUser(UserID uid, User& user) const;
	bool createUser(UserID uid);
	bool createUser(UserID uid, Cash cash); // should exist but needed for testing

	bool fetchStorage(Inventory& inventory) const;

	void clear();

	Server(string path = "./TESTING/");

};

