#include "stdafx.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.material.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.damagesource.h"
#include "net.minecraft.h"
#include "net.minecraft.world.h"
#include "EndactusTile.h"

EndactusTile::EndactusTile(int id) : Tile(id, Material::wood,isSolidRender())
{
	setTicking(true);
	iconTop = nullptr;
	iconBottom = nullptr;
}

void EndactusTile::tick(Level *level, int x, int y, int z, Random *random)
{
	if (level->isEmptyTile(x, y + 1, z))
	{ 
		int height = 1;
		while (level->getTile(x, y - height, z) == id)
		{
			height++;
		}
		if (height < 9)
		{
			int age = level->getData(x, y, z);
			if (age == 15)
			{
				level->setTileAndUpdate(x, y + 1, z, id);
				level->setData(x, y, z, 0, Tile::UPDATE_NONE);
				neighborChanged(level, x, y + 1, z, id);
			}
			else
			{
				level->setData(x, y, z, age + 1, Tile::UPDATE_NONE);
			}
		}
	}
}

AABB *EndactusTile::getAABB(Level *level, int x, int y, int z)
{
	float r = 1 / 16.0f;
	return AABB::newTemp(x + r, y, z + r, x + 1 - r, y + 1 - r, z + 1 - r);

}

AABB *EndactusTile::getTileAABB(Level *level, int x, int y, int z)
{
	float r = 1 / 16.0f;
	return AABB::newTemp(x + r, y, z + r, x + 1 - r, y + 1, z + 1 - r);
}

Icon *EndactusTile::getTexture(int face, int data)
{
	if (face == Facing::UP) return iconTop;
	if (face == Facing::DOWN) return iconBottom;
	else return icon;
}

bool EndactusTile::isCubeShaped()
{
	return false;
}

bool EndactusTile::isSolidRender(bool isServerLevel)
{
	return false;
}

int EndactusTile::getRenderShape()
{
	return Tile::SHAPE_CACTUS;
}

bool EndactusTile::mayPlace(Level *level, int x, int y, int z)
{
	if (!Tile::mayPlace(level, x, y, z)) return false;

	return canSurvive(level, x, y, z);
}

void EndactusTile::neighborChanged(Level *level, int x, int y, int z, int type)
{
	if (!canSurvive(level, x, y, z))
	{
		level->destroyTile(x, y, z, true);
	}
}

bool EndactusTile::canSurvive(Level *level, int x, int y, int z)
{
	int below = level->getTile(x, y - 1, z);
	return below == Tile::endactus_Id || below == Tile::endSand_Id;
}

void EndactusTile::entityInside(Level *level, int x, int y, int z, shared_ptr<Entity> entity)
{
	entity->hurt(DamageSource::cactus, 1);
}

void EndactusTile::registerIcons(IconRegister *iconRegister)
{
	icon = iconRegister->registerIcon(L"endactus_side");
	iconTop = iconRegister->registerIcon(L"endactus_top");
	iconBottom = iconRegister->registerIcon(L"endactus_bottom");
}

bool EndactusTile::shouldTileTick(Level *level, int x,int y,int z)
{
	return level->isEmptyTile(x, y + 1, z);
}
