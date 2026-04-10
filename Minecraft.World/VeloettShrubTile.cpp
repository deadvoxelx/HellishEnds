#include "stdafx.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "VeloettShrubTile.h"

VeloettShrubTile::VeloettShrubTile(int id) : Bush(id,Material::replaceable_plant)
{
    updateDefaultShape();
}

void VeloettShrubTile::updateDefaultShape()
{
    float ss = 0.4f;
    this->setShape(0.5f - ss, 0, 0.5f - ss, 0.5f + ss, 0.8f, 0.5f + ss);
}

bool VeloettShrubTile::mayPlaceOn(int tile)
{
	return tile == Tile::veloettGrass_Id;
}

int VeloettShrubTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Item::veloettBerry->id;
}

int VeloettShrubTile::getResourceCount(Random *random)
{
	return 1 + random->nextInt(2);
}

int VeloettShrubTile::getResourceCountForLootBonus(int bonusLevel, Random *random)
{
	return getResourceCount(random) + random->nextInt(bonusLevel + 1);
}

shared_ptr<ItemInstance> VeloettShrubTile::getSilkTouchItemInstance(int data)
{
	return shared_ptr<ItemInstance>(new ItemInstance(Tile::veloettShrub));
}

void VeloettShrubTile::spawnResources(Level *level, int x, int y, int z, int data, float odds,  int playerBonusLevel)
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
			popResource(level, x, y, z, std::make_shared<ItemInstance>(Item::veloettBerry_Id, 1, 0));
		}
	}
}
