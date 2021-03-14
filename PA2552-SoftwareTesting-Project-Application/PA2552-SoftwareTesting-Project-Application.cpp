#include <iostream>
#include "Server.h"
#include "User.h"

string asString(const Item& item) {
	string ret = "";
	ret += item.getName() + " : " + to_string(item.getPrice()) + "$";
	return ret;
}

void print_user(User& user) {
	cout << " --- " << user.getUsername() << " --- " << endl;
	cout << "Inventory:" << endl;
	Inventory& inv = user.getInventory();
	for (size_t i = 0; i < inv.size(); i++)
	{
		cout << "   - " << asString(inv[i]) << endl;
	}
}

Item createItem() {
	string name;
	float price;
	string desc;
	cout << "Name: ";
	cin >> name;
	cout << "Price: ";
	cin >> price;
	cout << "Description: ";
	cin >> desc;
	return Item(name, price, desc);
}

string getInput() {
	cout << "Input: ";
	string ret;
	cin >> ret;
	return ret;
}

int main() {
	Server server("./live/");

	struct Command {
		string activator;
		string	description;
		string asString() const {
			return "(" + activator + ") " + description;
		}
		Command(string act, string desc) {
			activator = act;
			description = desc;
		}
	};
	vector<Command> commands = {
		Command("q","Quit"),
		Command("inv","Show Inventory"),
		Command("create","Create Item")
	};

	bool running = true;
	while (running)
	{
		cout << " <- " << "Commands" << " -> " << endl;
		for (size_t i = 0; i < commands.size(); i++)
		{
			cout << "   - " <<commands[i].asString() << endl;
		}

		string input = getInput();

		for (size_t i = 0; i < commands.size(); i++)
		{
			if (commands[i].activator == input) {
				switch (i)
				{
				case 0: // quit
					running = false;
					break;
				case 1: // inventory
					break;
				case 2: // create
					break;
				default:
					break;
				}
			}
		}

	}

	return 0;
}