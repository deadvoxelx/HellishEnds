#pragma once
#include "Tile.h"

class Random;

class Glowstonetile : public Tile
{
public:
    Glowstonetile(int id, Material *material);
    virtual int getResourceCount(Random *random);
    virtual int getResource(int data, Random *random, int playerBonusLevel);
};
