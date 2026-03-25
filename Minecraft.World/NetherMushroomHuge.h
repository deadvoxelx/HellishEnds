#pragma once
#include "Feature.h"

class NetherMushroomHugeFeature : public Feature
{
private:
	int forcedType;

public:
	NetherMushroomHugeFeature(int forcedType);
	NetherMushroomHugeFeature();
	virtual bool place(Level *level, Random *random, int x, int y, int z);
};
