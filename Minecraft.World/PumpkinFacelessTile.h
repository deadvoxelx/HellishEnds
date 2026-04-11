#pragma once
#include "Tile.h"

class ChunkRebuildData;
class PumpkinFacelessTile : public Tile
{
	friend class ChunkRebuildData;
private:
	Icon *iconTop;
public:
	PumpkinFacelessTile(int id);
public:
	virtual Icon *getTexture(int face, int data);
	void registerIcons(IconRegister *iconRegister);
};