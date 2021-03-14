#pragma once
#include <string>
using namespace std;

typedef string ItemID;
typedef float Cash;

class Item {
private:
	ItemID m_name = "";
	Cash m_price;
	string m_description;

public:
	void setName(ItemID name);
	void setPrice(Cash price);
	void setDescription(string description);

	ItemID getName() const;
	Cash getPrice() const;
	string getDescription() const;
	bool isEmpty() const;

	Item(ItemID name, Cash price = 0, string description = "");
	Item();

	bool operator==(const Item& other) const;

};

