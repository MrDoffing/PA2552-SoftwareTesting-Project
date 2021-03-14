#include "User.h"

void User::setUsername(UserID username)
{
	m_username = username;
}

void User::setBankValue(Cash value)
{
	m_bank = value;
}

string User::getUsername() const
{
	return m_username;
}

Cash User::getBankValue() const
{
	return m_bank;
}

Inventory& User::getInventory()
{
	return m_inventory;
}

bool User::withdraw(Cash value)
{
	if (m_bank >= value) {
		m_bank -= value;
		return true;
	}
	return false;
}

void User::deposit(Cash value)
{
	m_bank += value;
}

User::User(UserID username, Cash bankValue)
{
	setUsername(username);
	setBankValue(bankValue);
}
