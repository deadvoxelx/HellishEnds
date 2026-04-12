#include "stdafx.h"
#include "WhiteEndermanRenderer.h"
#include "EndermanModel.h"
#include "TextureAtlas.h"
#include "..\Minecraft.World\net.minecraft.world.entity.monster.h"
#include "..\Minecraft.World\net.minecraft.world.level.tile.h"

ResourceLocation WhiteEndermanRenderer::WHITE_ENDERMAN_EYES_LOCATION = ResourceLocation(TN_MOB_WHITE_ENDERMAN_EYES);
ResourceLocation WhiteEndermanRenderer::WHITE_ENDERMAN_LOCATION = ResourceLocation(TN_MOB_WHITE_ENDERMAN);

WhiteEndermanRenderer::WhiteEndermanRenderer() : MobRenderer(new EndermanModel(), 0.5f)
{
	model = static_cast<EndermanModel *>(MobRenderer::model);
	this->setArmor(model);
}

void WhiteEndermanRenderer::render(shared_ptr<Entity> _mob, double x, double y, double z, float rot, float a)
{
	shared_ptr<WhiteEnderman> mob = dynamic_pointer_cast<WhiteEnderman>(_mob);

	model->creepy = mob->isCreepy();

	if (mob->isCreepy())
	{
		double d = 0.02;
		x += random.nextGaussian() * d;
		z += random.nextGaussian() * d;
	}

	MobRenderer::render(mob, x, y, z, rot, a);
}

ResourceLocation *WhiteEndermanRenderer::getTextureLocation(shared_ptr<Entity> mob)
{
    return &WHITE_ENDERMAN_LOCATION;
}

void WhiteEndermanRenderer::additionalRendering(shared_ptr<LivingEntity> _mob, float a)
{
	shared_ptr<WhiteEnderman> mob = dynamic_pointer_cast<WhiteEnderman>(_mob);

	MobRenderer::additionalRendering(_mob, a);
}

int WhiteEndermanRenderer::prepareArmor(shared_ptr<LivingEntity> _mob, int layer, float a)
{
	shared_ptr<WhiteEnderman> mob = dynamic_pointer_cast<WhiteEnderman>(_mob);

	if (layer != 0) return -1;

	bindTexture(&WHITE_ENDERMAN_EYES_LOCATION);
	float br = 1;
	glEnable(GL_BLEND);
#ifdef _XBOX
    glDisable(GL_ALPHA_TEST);
#endif
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_LIGHTING);

	if (mob->isInvisible())
	{
		glDepthMask(false);
	}
    else
	{
		glDepthMask(true);
	}

	if (SharedConstants::TEXTURE_LIGHTING)
	{
		int col = 0xf0f0;
		int u = col % 65536;
		int v = col / 65536;

		glMultiTexCoord2f(GL_TEXTURE1, u / 1.0f, v / 1.0f);
		glColor4f(1, 1, 1, 1);
	}

	glEnable(GL_LIGHTING);
	glColor4f(1, 1, 1, br);
	return 1;
}