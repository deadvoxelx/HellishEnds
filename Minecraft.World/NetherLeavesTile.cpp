#include "stdafx.h"
#include "NetherLeavesTile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"

NetherLeavesTile::NetherLeavesTile(int id) : TransparentTile(id, Material::leaves, true)
{
}

int NetherLeavesTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Item::stick->id;
	//return Tile::netherSapling_Id + type;
}

int NetherLeavesTile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	return getResourceCount(random) + random->nextInt(bonusLevel + 1);
}

int NetherLeavesTile::getResourceCount(Random *random)
{
	return 1 + random->nextInt(2);
}

shared_ptr<ItemInstance> NetherLeavesTile::getSilkTouchItemInstance(int data)
{
	return shared_ptr<ItemInstance>(new ItemInstance(Tile::netherLeaves));
}

void NetherLeavesTile::spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel)
{
	Tile::spawnResources(level, x, y, z, data, odds, playerBonusLevel);
}