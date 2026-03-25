#include "stdafx.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.damagesource.h"
#include "HellSphere.h"



void HellSphere::_init()
{
	// 4J Stu - This function call had to be moved here from the Entity ctor to ensure that
	// the derived version of the function is called
	this->defineSynchedData();
}

HellSphere::HellSphere(Level *level) : Throwable(level)
{
	_init();
}

HellSphere::HellSphere(Level *level, shared_ptr<LivingEntity> mob) : Throwable(level,mob)
{
	_init();
}

HellSphere::HellSphere(Level *level, double x, double y, double z) : Throwable(level,x,y,z)
{
	_init();
}

void HellSphere::onHit(HitResult *res)
{
	if (res->entity != NULL)
	{
		int damage = 3;

		DamageSource *damageSource = DamageSource::thrown(shared_from_this(), getOwner());
		res->entity->hurt(damageSource, damage);
		delete damageSource;
	}
	for (int i = 0; i < 8; i++)
		level->addParticle(eParticleType_snowballpoof, x, y, z, 0, 0, 0);
	if (!level->isClientSide)
	{
		remove();
		explode();
	}
}

void HellSphere::explode()
{
	float r = 3.0f;
	level->explode(shared_from_this(), x, y, z, r, true);
}