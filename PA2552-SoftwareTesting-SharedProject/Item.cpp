#include "Item.h"

void Item::setName(ItemID name)
{
    m_name = name;
}

void Item::setPrice(Cash price)
{
    m_price = price;
}

void Item::setDescription(string description)
{
    m_description = description;
}

ItemID Item::getName() const
{
    return m_name;
}

Cash Item::getPrice() const
{
    return m_price;
}

string Item::getDescription() const
{
    return m_description;
}

bool Item::isEmpty() const
{
    return (m_name == "");
}

Item::Item(ItemID name, Cash price, string description)
{
    setName(name);
    setPrice(price);
    setDescription(description);
}

Item::Item()
{
}

bool Item::operator==(const Item& other) const
{
    return memcmp(this, &other, sizeof(*this));
}
