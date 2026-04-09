#pragma once
#include "Feature.h"

class Level;

class VeloettShrubFeature : public Feature
{
public:
    virtual bool place(Level *level, Random *random, int x, int y, int z);
};