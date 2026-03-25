#pragma once
using namespace std;

#include "Item.h"

class HellSphereItem : public Item
{
public:
	HellSphereItem(int id);

	virtual shared_ptr<ItemInstance> use(shared_ptr<ItemInstance> instance, Level *level, shared_ptr<Player> player);
};