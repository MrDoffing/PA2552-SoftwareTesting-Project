#pragma once
#include <vector>
#include <fstream>
#include "Item.h"
class Inventory
{
private:
	vector<Item> m_items;

public:
	int size() const;

	void push(const Item& item);
	Item pop(ItemID name);

	Item& get(int index);
	Item* get(ItemID name);

	Item& operator[](const int& index);
	Inventory& operator<<(fstream& file);
	Inventory& operator>>(fstream& file);
	bool operator==(const Inventory& other);

};

