#include "BiomeDecorator.h"
#include "EndGatewayFeature.h"

class TheOuterEndBiomeDecorator : public BiomeDecorator
{
public:
	TheOuterEndBiomeDecorator(Biome *biome);

protected:
	EndGatewayFeature *endGatewayFeature;
	virtual void decorate();
};