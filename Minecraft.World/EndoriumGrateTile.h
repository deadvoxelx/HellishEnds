#pragma once
#include "TransparentTile.h"

class EndoriumGrateTile : public TransparentTile
{
	friend class Tile;
protected:
	EndoriumGrateTile(int id);
};