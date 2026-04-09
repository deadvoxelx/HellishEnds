#include "stdafx.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "VeloettFlowerTile.h"

VeloettFlowerTile::VeloettFlowerTile(int id) : Bush(id,Material::replaceable_plant)
{
    updateDefaultShape();
}

void VeloettFlowerTile::updateDefaultShape()
{
    float ss = 0.4f;
    this->setShape(0.5f - ss, 0, 0.5f - ss, 0.5f + ss, 0.8f, 0.5f + ss);
}

bool VeloettFlowerTile::mayPlaceOn(int tile)
{
	return tile == Tile::veloettGrass_Id;
}

bool VeloettFlowerTile::growTree(Level *level, int x, int y, int z, Random *random)
{
	int data = level->getData(x, y, z);

	level->removeTile(x, y, z);
	Feature *f = NULL;

	if (id == Tile::veloettFlower_Id)
	{
		f = new PurulTreeFeature(1);
	}

	if (f == NULL || !f->place(level, random, x, y, z))
	{
		level->setTileAndData(x, y, z, id, data, Tile::UPDATE_ALL);
		if( f != NULL )
			delete f;
		return false;
	}
	if( f != NULL )
		delete f;
	return true;
}