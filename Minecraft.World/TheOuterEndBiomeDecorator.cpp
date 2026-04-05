#define _USE_MATH_DEFINES
#include <cmath>
#include "stdafx.h"
#include "TheOuterEndBiomeDecorator.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.level.levelgen.feature.h"
#include "EndGatewayFeature.h"

const double M_PI = 3.14159265358979323846;

TheOuterEndBiomeDecorator::TheOuterEndBiomeDecorator(Biome *biome) : BiomeDecorator(biome)
{
	endGatewayFeature = new EndGatewayFeature(Tile::unbreakable_Id);
}

void TheOuterEndBiomeDecorator::decorate()
{
	decorateOres();

	// this will only set the y to the top y of the chunks already processed...
	int y = level->getTopSolidBlock(xo+8, zo+8);
	if(y>level->GetHighestY()) level->SetHighestY(y);

	if (xo == 0 && zo == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			
			double angle = (2 * M_PI / 20) * i;

			int gx = (int)(96 * cos(angle));
			int gz = (int)(96 * sin(angle));


			endGatewayFeature->place(level, random, gx, 75, gz);
		}
	}
}