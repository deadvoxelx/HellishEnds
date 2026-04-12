#pragma once
#include "MobRenderer.h"

class WhiteEnderman;
class EndermanModel;

class WhiteEndermanRenderer : public MobRenderer
{
private:
	EndermanModel *model;
	Random random;
	static ResourceLocation WHITE_ENDERMAN_EYES_LOCATION;
	static ResourceLocation WHITE_ENDERMAN_LOCATION;

public:
	WhiteEndermanRenderer();

	void render(shared_ptr<Entity> _mob, double x, double y, double z, float rot, float a);
	ResourceLocation *getTextureLocation(shared_ptr<Entity> mob);
	void additionalRendering(shared_ptr<LivingEntity> _mob, float a);

protected:
	int prepareArmor(shared_ptr<LivingEntity> _mob, int layer, float a);
};