#pragma once
#include "Inventory.h"

typedef string UserID;

class User
{
private:
	UserID m_username;
	Cash m_bank;
	Inventory m_inventory;

public:
	void setUsername(UserID username);
	void setBankValue(Cash value);

	string getUsername() const;
	Cash getBankValue() const;
	Inventory& getInventory();

	bool withdraw(Cash value);
	void deposit(Cash value);

	User(UserID username = "", Cash bankValue = 0);

};

