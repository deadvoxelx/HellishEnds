#pragma once
#include "Tile.h"

class NetherSoilTile : public Tile
{
	friend class Tile;
protected:
	NetherSoilTile(int id);
};