#include "stdafx.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "EndesertBushTile.h"

EndesertBushTile::EndesertBushTile(int id) : Bush(id,Material::replaceable_plant)
{
    updateDefaultShape();
}

void EndesertBushTile::updateDefaultShape()
{
    float ss = 0.4f;
    this->setShape(0.5f - ss, 0, 0.5f - ss, 0.5f + ss, 0.8f, 0.5f + ss);
}

bool EndesertBushTile::mayPlace(Level *level, int x, int y, int z)
{
	if (!Tile::mayPlace(level, x, y, z)) return false;

	return canSurvive(level, x, y, z);
}

bool EndesertBushTile::canSurvive(Level *level, int x, int y, int z)
{
	int below = level->getTile(x, y - 1, z);
	return below == Tile::sand_Id || below == Tile::endSand_Id || below == Tile::endStone_Id;
}

int EndesertBushTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Item::stick->id;
}

int EndesertBushTile::getResourceCount(Random *random)
{
	return 1 + random->nextInt(2);
}

int EndesertBushTile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	return getResourceCount(random) + random->nextInt(bonusLevel + 1);
}

shared_ptr<ItemInstance> EndesertBushTile::getSilkTouchItemInstance(int data)
{
	return shared_ptr<ItemInstance>(new ItemInstance(Tile::endesertBush));
}

void EndesertBushTile::spawnResources(Level *level, int x, int y, int z, int data, float odds,  int playerBonusLevel)
{
	if (!level->isClientSide)
	{
		int chance = 2;

		chance = 2;
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
			popResource(level, x, y, z, std::make_shared<ItemInstance>(Item::stick_Id, 1, 0));
		}
	}
}