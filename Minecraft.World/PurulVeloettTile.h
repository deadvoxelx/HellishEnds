#pragma once
#include "Tile.h"

class PurulVeloettTile : public Tile
{
	friend class Tile;
protected:
	PurulVeloettTile(int id);
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);

public:
	virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual int getResourceCountForLootBonus(int bonusLevel, Random *random);
	virtual int getResourceCount(Random *random);
	virtual void spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel);
};