#pragma once
using namespace std;

#include "Item.h"

class Player;

class ShearsItem : public Item 
{
public:
	ShearsItem(int itemId);
	virtual bool mineBlock(shared_ptr<ItemInstance> itemInstance, Level *level, int tile, int x, int y, int z, shared_ptr<LivingEntity> owner);
	virtual bool canDestroySpecial(Tile *tile);
	virtual float getDestroySpeed(shared_ptr<ItemInstance> itemInstance, Tile *tile);
	virtual bool useOn(shared_ptr<ItemInstance> instance, shared_ptr<Player> player, Level *level, int x, int y, int z, int face, float clickX, float clickY, float clickZ, bool bTestUseOnOnly=false);
};
