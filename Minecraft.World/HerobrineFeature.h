#pragma once
#include "Feature.h"

class HerobrineFeature : public Feature
{
public:
    HerobrineFeature(int blockId);

    virtual bool place(Level *level, Random *random, int x, int y, int z);
};