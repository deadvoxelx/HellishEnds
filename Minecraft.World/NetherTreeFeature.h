#pragma once
#include "Feature.h"
class Level;

class NetherTreeFeature : public Feature
{
public:
	virtual bool place(Level *level, Random *random, int x, int y, int z);
private:
	void addVine(Level *level, int xx, int yy, int zz, int dir);
};