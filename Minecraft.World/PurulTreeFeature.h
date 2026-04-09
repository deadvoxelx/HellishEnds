#pragma once
#include "Feature.h"

class PurulTreeFeature : public Feature
{
private:
	int forcedType;

public:
	PurulTreeFeature(int forcedType);
	PurulTreeFeature();
	virtual bool place(Level *level, Random *random, int x, int y, int z);
};
