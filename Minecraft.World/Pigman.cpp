#include "stdafx.h"
#include "com.mojang.nbt.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.ai.attributes.h"
#include "net.minecraft.world.entity.ai.goal.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "net.minecraft.world.entity.item.h"
#include "net.minecraft.world.entity.monster.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.entity.global.h"
#include "Pigman.h"
#include "..\Minecraft.Client\Textures.h"
#include "MobCategory.h"



Pigman::Pigman(Level *level) : Animal( level )
{
	// 4J Stu - This function call had to be moved here from the Entity ctor to ensure that
	// the derived version of the function is called
	this->defineSynchedData();
	registerAttributes();
	setHealth(getMaxHealth());

	setSize(0.6f, 1.8f);

	getNavigation()->setAvoidWater(true);
	goalSelector.addGoal(0, new FloatGoal(this));
	goalSelector.addGoal(1, new PanicGoal(this, 1.25));
	goalSelector.addGoal(2, new MoveIndoorsGoal(this));
	goalSelector.addGoal(3, new RestrictOpenDoorGoal(this));
	goalSelector.addGoal(4, new OpenDoorGoal(this, true));
	goalSelector.addGoal(5, new MoveTowardsRestrictionGoal(this, 1.0));
	goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0));
	goalSelector.addGoal(7, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(8, new RandomLookAroundGoal(this));
}

bool Pigman::useNewAi()
{
	return true;
}

void Pigman::registerAttributes()
{
	Animal::registerAttributes();

	getAttribute(SharedMonsterAttributes::MAX_HEALTH)->setBaseValue(20);
	getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED)->setBaseValue(0.25f);
}

void Pigman::newServerAiStep()
{
	Animal::newServerAiStep();
}


int Pigman::getAmbientSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
}

int Pigman::getHurtSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
}

int Pigman::getDeathSound() 
{
	return eSoundType_MOB_PIG_DEATH;
}

void Pigman::playStepSound(int xt, int yt, int zt, int t)
{
	playSound(eSoundType_MOB_PIG_STEP, 0.15f, 1);
}

int Pigman::getDeathLoot() 
{
	if (this->isOnFire() ) return Item::porkChop_cooked->id;
	return Item::porkChop_raw_Id;
}

void Pigman::dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel)
{
	int count = random->nextInt(3) + 1 + random->nextInt(1 + playerBonusLevel);

	for (int i = 0; i < count; i++)
	{
		if (isOnFire())
		{
			spawnAtLocation(Item::porkChop_cooked_Id, 1);
		}
		else
		{
			spawnAtLocation(Item::porkChop_raw_Id, 1);
		}
	}
}

void Pigman::thunderHit(const LightningBolt *lightningBolt)
{
	if (level->isClientSide) return;
	shared_ptr<PigZombie> pz = std::make_shared<PigZombie>(level);
	pz->moveTo(x, y, z, yRot, xRot);
	level->addEntity(pz);
	remove();
}

shared_ptr<AgableMob> Pigman::getBreedOffspring(shared_ptr<AgableMob> target)
{
	// 4J - added limit to number of animals that can be bred
	if( level->canCreateMore( GetType(), Level::eSpawnType_Breed) )
	{
		return std::make_shared<Pigman>(level);
	}
	else
	{
		return nullptr;
	}
}

bool Pigman::removeWhenFarAway()
{
	return false;
}