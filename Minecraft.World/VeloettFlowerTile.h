#pragma once
#include "Bush.h"

class Random;

class VeloettFlowerTile : public Bush
{
	friend class Tile;
protected:
	VeloettFlowerTile(int id);
    virtual bool mayPlaceOn(int tile);
public:
    virtual void updateDefaultShape(); // 4J Added override

	bool growTree(Level *level, int x, int y, int z, Random *random);
};
