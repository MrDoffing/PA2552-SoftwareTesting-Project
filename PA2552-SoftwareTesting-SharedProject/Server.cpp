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

bool Server::buy(UserID uid, ItemID iid)
{
	// collect
	Inventory inventory;
	readStorage(inventory);
	User user;
	readUser(uid, user);
	Item* ptr_item = inventory.get(iid);
	// pay
	if (user.withdraw(ptr_item->getPrice())) {
		// transfer item
		user.getInventory().push(inventory.pop(iid));
		// update database
		writeStorage(inventory);
		writeUser(user);
		return true;
	}
	return false;
}

void Server::sell(UserID uid, ItemID iid)
{
	// collect
	Inventory inventory;
	readStorage(inventory);
	User user;
	readUser(uid, user);
	// transfer item
	Item item = user.getInventory().pop(iid);
	inventory.push(item);
	// retrieve cash from item
	user.deposit(item.getPrice());
	// update database
	writeStorage(inventory);
	writeUser(user);
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
	setPath(path);
	// create if non exist
	Inventory inv;
	if (readStorage(inv) == false)
		writeStorage(inv);
}
