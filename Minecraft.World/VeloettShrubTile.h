#pragma once
#include "Bush.h"

class Random;

class VeloettShrubTile : public Bush
{
	friend class Tile;
protected:
	VeloettShrubTile(int id);
    virtual bool mayPlaceOn(int tile);
	virtual shared_ptr<ItemInstance> getSilkTouchItemInstance(int data);
public:
    virtual void updateDefaultShape(); // 4J Added override
    virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual int getResourceCount(Random *random);
	virtual int getResourceCountForLootBonus(int bonusLevel, Random *random);
	virtual void spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel);
};
