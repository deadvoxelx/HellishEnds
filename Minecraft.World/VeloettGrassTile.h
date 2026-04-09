#pragma once
#include "Tile.h"

class ChunkRebuildData;
class VeloettGrassTile : public Tile
{
	friend class ChunkRebuildData;
private:
	Icon *iconTop;
	Icon *iconBottom;
public:
	VeloettGrassTile(int id);
public:
	virtual Icon *getTexture(int face, int data);
	void registerIcons(IconRegister *iconRegister);
};