#include "items.h"

Item::Item() {}

Item::Item(std::string name, int id, int cost, std::string description, int healamount) {
	m_itemName = name;
	m_itemId = id;
	m_itemCost = cost;
	m_itemDescription = description;
	m_healAmount = healamount;
}