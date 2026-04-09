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
	return 1;
}

void VeloettShrubTile::playerDestroy(Level *level, shared_ptr<Player> player, int x, int y, int z, int data)
{
	VeloettShrubTile::playerDestroy(level, player, x, y, z, data);
	popResource(level, x, y, z, std::make_shared<ItemInstance>(Tile::veloettShrub, 1, data));
}
