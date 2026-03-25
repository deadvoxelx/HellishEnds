#pragma once
#include "TransparentTile.h"

class NetherLeavesTile : public TransparentTile
{
	friend class Tile;
protected:
	NetherLeavesTile(int id);
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);

public:
	virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual int getResourceCountForLootBonus(int bonusLevel, Random *random);
	virtual int getResourceCount(Random *random);
	virtual void spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel);
private:
	int type;
};