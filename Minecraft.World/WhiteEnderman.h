#pragma once

#include "Monster.h"

class WhiteEnderman : public Monster
{
public:
	eINSTANCEOF GetType() { return eTYPE_WHITE_ENDERMAN; }
	static Entity *create(Level *level) { return new WhiteEnderman(level); }
public:
	static void staticCtor();
private:
	static AttributeModifier *SPEED_MODIFIER_ATTACKING;

	static const int DATA_CREEPY = 18;

private:
	int angerTime;
	shared_ptr<Entity> lastAttackTarget;
	bool aggroedByPlayer;

public:
	WhiteEnderman(Level *level);

protected:
	virtual void registerAttributes();
	virtual void defineSynchedData();

public:
	virtual void addAdditonalSaveData(CompoundTag *tag);
	virtual void readAdditionalSaveData(CompoundTag *tag);

protected:
	virtual shared_ptr<Entity> findAttackTarget();

public:
	virtual void aiStep();

protected:
	virtual int getAmbientSound();
	virtual int getHurtSound();
	virtual int getDeathSound();
	virtual int getDeathLoot();
	virtual void dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel);

public:
	virtual bool hurt(DamageSource *source, float damage);
	bool isCreepy();
	void setCreepy(bool creepy);

private:
	void alert(shared_ptr<Entity> target);
};