#include "stdafx.h"
#include "PurulVeloettTile.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"

PurulVeloettTile::PurulVeloettTile(int id) : Tile(id, Material::leaves, true)
{
}

int PurulVeloettTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Tile::veloettFlower->id;
}

int PurulVeloettTile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	return getResourceCount(random) + random->nextInt(bonusLevel + 1);
}

int PurulVeloettTile::getResourceCount(Random *random)
{
	return 1 + random->nextInt(3);
}

shared_ptr<ItemInstance> PurulVeloettTile::getSilkTouchItemInstance(int data)
{
	return shared_ptr<ItemInstance>(new ItemInstance(Tile::purulVeloett));
}

void PurulVeloettTile::spawnResources(Level *level, int x, int y, int z, int data, float odds, int playerBonusLevel)
{
	if (!level->isClientSide)
	{
		int chance = 5;

		chance = 5;
		if (playerBonusLevel > 0)
		{
			chance -= 1 << playerBonusLevel;
			if (chance < 2)
			{
				chance = 2;
			}
		}
		if (level->random->nextInt(chance) == 0)
		{
			popResource(level, x, y, z, std::make_shared<ItemInstance>(Tile::veloettFlower_Id, 1, 0));
		}
	}
}