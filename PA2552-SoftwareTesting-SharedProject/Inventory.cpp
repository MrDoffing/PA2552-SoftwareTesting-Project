#include "Inventory.h"

int Inventory::size() const
{
    return m_items.size();
}

void Inventory::push(const Item& item)
{
    m_items.push_back(item);
}

Item Inventory::pop(ItemID name)
{
    Item it;
    for (size_t i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].getName() == name) {
            it = m_items[i];
            m_items.erase(m_items.begin()+i);
            break;
        }
    }
    return it;
}

Item& Inventory::get(int index)
{
    return m_items[index];
}

Item* Inventory::get(ItemID name)
{
    for (size_t i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].getName() == name)
            return &m_items[i];
    }
    return nullptr;
}

Item& Inventory::operator[](const int& index)
{
    return m_items[index];
}

Inventory& Inventory::operator<<(fstream& file)
{
    m_items.clear();
    unsigned char c = file.peek();
    while (file.peek() == '@')
    {
        string hashTemp;
        string name;
        float price;
        string desc;
        file >> hashTemp >> name >> price >> desc;
        file.get(); // newline
        m_items.push_back(Item(name, price, desc));
    }
    return *this;
}

Inventory& Inventory::operator>>(fstream& file)
{
    for (size_t i = 0; i < m_items.size(); i++)
    {
        file << "@ ";
        file << m_items[i].getName() << " ";
        file << m_items[i].getPrice() << " ";
        file << m_items[i].getDescription() << endl;
    }
    return *this;
}

bool Inventory::operator==(const Inventory& other)
{
    return m_items == other.m_items;
}

