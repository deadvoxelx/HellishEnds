#include "stdafx.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.ai.attributes.h"
#include "net.minecraft.world.entity.monster.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.damagesource.h"
#include "net.minecraft.world.phys.h"
#include "com.mojang.nbt.h"
#include "..\Minecraft.Client\Textures.h"
#include "WhiteEnderman.h"

AttributeModifier *WhiteEnderman::SPEED_MODIFIER_ATTACKING = (new AttributeModifier(eModifierId_MOB_ENDERMAN_ATTACKSPEED, 6.2f, AttributeModifier::OPERATION_ADDITION))->setSerialize(false);

void WhiteEnderman::staticCtor()
{
}

WhiteEnderman::WhiteEnderman(Level *level) : Monster( level )
{
	this->defineSynchedData();
	registerAttributes();
	setHealth(getMaxHealth());

	angerTime = 0;
	lastAttackTarget = nullptr;
	aggroedByPlayer = false;

	setSize(0.6f, 2.9f);
	footSize = 1;
}

void WhiteEnderman::registerAttributes()
{
	Monster::registerAttributes();

	getAttribute(SharedMonsterAttributes::MAX_HEALTH)->setBaseValue(40);
	getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED)->setBaseValue(0.3f);
	getAttribute(SharedMonsterAttributes::ATTACK_DAMAGE)->setBaseValue(7);
}

void WhiteEnderman::defineSynchedData()
{
	Monster::defineSynchedData();

	entityData->define(DATA_CREEPY, static_cast<byte>(0));
}

void WhiteEnderman::addAdditonalSaveData(CompoundTag *tag)
{
	Monster::addAdditonalSaveData(tag);
	tag->putShort(L"Anger", static_cast<short>(angerTime));
}

void WhiteEnderman::readAdditionalSaveData(CompoundTag *tag)
{
	Monster::readAdditionalSaveData(tag);
	angerTime = tag->getShort(L"Anger");
}

shared_ptr<Entity> WhiteEnderman::findAttackTarget()
{
#ifndef _FINAL_BUILD
	if(app.GetMobsDontAttackEnabled())
	{
		return shared_ptr<Player>();
	}
#endif
	if (angerTime == 0) return nullptr;
	return nullptr;
}

void WhiteEnderman::aiStep()
{
	if (lastAttackTarget != attackTarget)
	{
		AttributeInstance *speed = getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED);
		speed->removeModifier(SPEED_MODIFIER_ATTACKING);

		if (attackTarget != nullptr)
		{
			speed->addModifier(new AttributeModifier(*SPEED_MODIFIER_ATTACKING));
		}
	}

	lastAttackTarget = attackTarget;

	for (int i = 0; i < 2; i++)
	{
		level->addParticle(eParticleType_ender, x + (random->nextDouble() - 0.5) * bbWidth, y + random->nextDouble() * bbHeight - 0.25f, z + (random->nextDouble() - 0.5) * bbWidth,
			(random->nextDouble() - 0.5) * 2, -random->nextDouble(), (random->nextDouble() - 0.5) * 2);
	}

	if (isOnFire())
	{
		attackTarget = nullptr;
		setCreepy(false);
		aggroedByPlayer = false;
	}

	if (isCreepy() && !aggroedByPlayer && random->nextInt(100) == 0)
	{
		setCreepy(false);
	}

	jumping = false;
	if (attackTarget != nullptr)
	{
		lookAt(attackTarget, 100, 100);
	}

	if (!level->isClientSide && isAlive())
	{
		if (attackTarget != nullptr)
		{
		}
		else
		{
			setCreepy(false);
		}
	}

	Monster::aiStep();
}

int WhiteEnderman::getAmbientSound()
{
	return isCreepy()? eSoundType_MOB_ENDERMAN_SCREAM : eSoundType_MOB_ENDERMEN_IDLE;
}

int WhiteEnderman::getHurtSound()
{
	return eSoundType_MOB_ENDERMEN_HIT;
}

int WhiteEnderman::getDeathSound()
{
	return eSoundType_MOB_ENDERMEN_DEATH;
}

int WhiteEnderman::getDeathLoot()
{
	return Item::enderPearl_Id;
}

void WhiteEnderman::dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel)
{
	int loot = getDeathLoot();
	if (loot > 0)
	{
		int count = random->nextInt(2 + playerBonusLevel);
		for (int i = 0; i < count; i++)
			spawnAtLocation(loot, 1);
	}
}

bool WhiteEnderman::hurt(DamageSource *source, float damage)
{
	shared_ptr<Entity> sourceEntity = source->getEntity();
	if ( sourceEntity != nullptr && sourceEntity->instanceof(eTYPE_PLAYER) )
	{
		if (!dynamic_pointer_cast<Player>(source->getEntity())->abilities.invulnerable)
		{
			vector<shared_ptr<Entity> > *nearby = level->getEntities( shared_from_this(), bb->grow(32, 32, 32));
			for (auto& e : *nearby)
			{
				if ( e->instanceof(eTYPE_WHITE_ENDERMAN) )
				{
					shared_ptr<WhiteEnderman> whiteEnderman = dynamic_pointer_cast<WhiteEnderman>(e);
					whiteEnderman->alert(sourceEntity);
				}
			}
			alert(sourceEntity);
		}
	}
	return Monster::hurt(source, damage);
}

void WhiteEnderman::alert(shared_ptr<Entity> target)
{
	attackTarget = target;
	angerTime = 20 * 20 + random->nextInt(20 * 20);
}


bool WhiteEnderman::isCreepy()
{
	return entityData->getByte(DATA_CREEPY) > 0;
}

void WhiteEnderman::setCreepy(bool creepy)
{
	entityData->set(DATA_CREEPY, static_cast<byte>(creepy ? 1 : 0));
}