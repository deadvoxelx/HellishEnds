#include "stdafx.h"
#include "NetherTreeFeature.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "JavaMath.h"

bool NetherTreeFeature::place(Level *level, Random *random, int x, int y, int z)
{
	int treeHeight = random->nextInt(4) + 5;
	while (level->getMaterial(x, y - 1, z) == Material::lava)
		y--;

	bool free = true;
	if (y < 1 || y + treeHeight + 1 > Level::genDepth) return false;

	for (int yy = y; yy <= y + 1 + treeHeight; yy++) 
	{
		int r = 1;
		if (yy == y) r = 0;
		if (yy >= y + 1 + treeHeight - 2) r = 3;
		for (int xx = x - r; xx <= x + r && free; xx++)
		{
			for (int zz = z - r; zz <= z + r && free; zz++)
			{
				if (yy >= 0 && yy < Level::genDepth)
				{
					int tt = level->getTile(xx, yy, zz);
					if (tt != 0 && tt != Tile::netherLeaves_Id)
					{
						if (tt == Tile::calmLava_Id || tt == Tile::lava_Id)
						{
							if (yy > y) free = false;
						}
						else
						{
							free = false;
						}
					}
				}
				else
				{
					free = false;
				}
			}
		}
	}

	if (!free) return false;

	int belowTile = level->getTile(x, y - 1, z);
	if ((belowTile != Tile::netherSoil_Id)) return false;

	placeBlock(level, x, y - 1, z, Tile::netherSoil_Id);

	for (int yy = y - 3 + treeHeight; yy <= y + treeHeight; yy++)
	{
		int yo = yy - (y + treeHeight);
		int offs = 2 - yo / 2;
		for (int xx = x - offs; xx <= x + offs; xx++)
		{
			int xo = xx - (x);
			for (int zz = z - offs; zz <= z + offs; zz++)
			{
				int zo = zz - (z);
				if (abs(xo) == offs && abs(zo) == offs && (random->nextInt(2) == 0 || yo == 0)) continue;
				if (!Tile::solid[level->getTile(xx, yy, zz)]) placeBlock(level, xx, yy, zz, Tile::netherLeaves_Id);
			}
		}
	}

	for (int hh = 0; hh < treeHeight; hh++)
	{
		int t = level->getTile(x, y + hh, z);
		if (t == 0 || t == Tile::netherLeaves_Id || t == Tile::lava_Id || t == Tile::calmLava_Id) placeBlock(level, x, y + hh, z, Tile::netherWood_Id);
	}

	for (int yy = y - 3 + treeHeight; yy <= y + treeHeight; yy++)
	{
		int yo = yy - (y + treeHeight);
		int offs = 2 - yo / 2;
		for (int xx = x - offs; xx <= x + offs; xx++)
		{
			for (int zz = z - offs; zz <= z + offs; zz++)
			{
				if (level->getTile(xx, yy, zz) == Tile::netherLeaves_Id)
				{
					if (random->nextInt(4) == 0 && level->getTile(xx - 1, yy, zz) == 0)
					{
						addVine(level, xx - 1, yy, zz, NetherVineTile::VINE_EAST);
					}
					if (random->nextInt(4) == 0 && level->getTile(xx + 1, yy, zz) == 0)
					{
						addVine(level, xx + 1, yy, zz, NetherVineTile::VINE_WEST);
					}
					if (random->nextInt(4) == 0 && level->getTile(xx, yy, zz - 1) == 0)
					{
						addVine(level, xx, yy, zz - 1, NetherVineTile::VINE_SOUTH);
					}
					if (random->nextInt(4) == 0 && level->getTile(xx, yy, zz + 1) == 0)
					{
						addVine(level, xx, yy, zz + 1, NetherVineTile::VINE_NORTH);
					}
				}
			}
		}
	}
	return true;

}

void NetherTreeFeature::addVine(Level *level, int xx, int yy, int zz, int dir)
{
    placeBlock(level, xx, yy, zz, Tile::netherVine_Id, dir);
    int maxDir = 4;
    while (level->getTile(xx, --yy, zz) == 0 && maxDir > 0)
	{
        placeBlock(level, xx, yy, zz, Tile::netherVine_Id, dir);
        maxDir--;
    }
}