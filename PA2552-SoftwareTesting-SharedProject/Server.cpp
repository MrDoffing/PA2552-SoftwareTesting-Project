#include "Server.h"

bool Server::readUser(UserID uid, User& user) const
{
	fstream file;
	file.open(m_relativePath+uid + ".txt", ios::in);
	string temp;
	if (file.is_open()) {
		UserID name;
		getline(file, name);
		user.setUsername(name);
		getline(file, temp);
		Cash bank = stof(temp);
		user.setBankValue(bank);
		user.getInventory() << file;
		file.close();
		return true;
	}
	return false;
}

bool Server::writeUser(User& user) const
{
	fstream file;
	file.open(m_relativePath+user.getUsername() + ".txt", ios::out);
	if (file.is_open()) {
		file << user.getUsername() << endl;
		file << user.getBankValue() << endl;
		user.getInventory() >> file;
		file.close();
		return true;
	}
	return false;
}

bool Server::writeStorage(Inventory& inventory) const
{
	fstream file;
	file.open(m_relativePath+ m_str_storage, ios::out);
	if (file.is_open()) {
		inventory >> file;
		file.close();
		return true;
	}
	return false;
}

bool Server::readStorage(Inventory& inventory) const
{
	fstream file;
	file.open(m_relativePath+ m_str_storage, ios::in);
	if (file.is_open()) {
		inventory << file;
		file.close();
		return true;
	}
	return false;
}

void Server::setPath(string path)
{
	if (path != "") {
		m_relativePath = path;
		filesystem::create_directory(path);
	}
}

bool Server::createItemForStorage(Item& item) const
{
	/*Inventory inv;
	if (!readStorage(inv)) return false;
	inv.push(item);
	if (!writeStorage(inv)) return false;
	return true;*/

	return false;
}

bool Server::createItemForUser(UserID uid, Item& item) const
{
	//read user info
	User user;
	if (!readUser(uid, user)) return false;
	// insert item to inventory
	user.getInventory().push(item);
	// write user to DB
	if (!writeUser(user))return false;
	return true;
}

bool Server::buy(UserID uid, ItemID iid) const
{
	// collect
	Inventory inventory;
	if (!readStorage(inventory)) return false;
	User user;
	if (!readUser(uid, user))return false;
	Item* ptr_item = inventory.get(iid);
	if (ptr_item != nullptr) {
		// pay
		if (user.withdraw(ptr_item->getPrice())) {
			// transfer item
			user.getInventory().push(inventory.pop(iid));
			// update database
			if (!writeStorage(inventory))return false;
			if (!writeUser(user))return false;
			return true;
		}
	}
	return false; // didnt find user
}

bool Server::sell(UserID uid, ItemID iid) const
{
	// collect
	Inventory inventory;
	if (!readStorage(inventory)) return false;
	User user;
	if (!readUser(uid, user)) return false;
	// transfer item
	Item item = user.getInventory().pop(iid);
	inventory.push(item);
	// retrieve cash from item
	user.deposit(item.getPrice());
	// update database
	if (!writeStorage(inventory))return false;
	if (!writeUser(user))return false;
	return true;
}

bool Server::fetchUser(UserID uid, User& user) const
{
	return readUser(uid, user);
}

bool Server::createUser(UserID uid)
{
	User user(uid);
	return writeUser(user);
}

bool Server::createUser(UserID uid, Cash cash)
{
	User user(uid, cash);
	return writeUser(user);
}

bool Server::fetchStorage(Inventory& inventory) const
{
	return readStorage(inventory);
}

void Server::clear()
{
	if (m_relativePath != "") {
		filesystem::remove_all(m_relativePath);
	}
}

Server::Server(string path)
{
	// set relative path
	setPath(path);
	// create storage if non exist
	Inventory inv;
	if (readStorage(inv) == false)
		writeStorage(inv);
}
