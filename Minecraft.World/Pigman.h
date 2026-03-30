#pragma once

using namespace std;

#include "Animal.h"

class Player;
class LightningBolt;

class Pigman : public Animal
{
public:
	eINSTANCEOF GetType() { return eTYPE_PIGMAN; }
	static Entity *create(Level *level){ return new Pigman(level); }

public:
	Pigman(Level *level);

	virtual bool useNewAi();

protected:
	virtual void registerAttributes();
	virtual void newServerAiStep();

protected:
	virtual bool removeWhenFarAway();
	virtual int getAmbientSound();
	virtual int getHurtSound();
	virtual int getDeathSound();
	virtual void playStepSound(int xt, int yt, int zt, int t);

protected:
	virtual int getDeathLoot();
	virtual void dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel);

public:
	virtual void thunderHit(const LightningBolt *lightningBolt);

public:
	virtual shared_ptr<AgableMob> getBreedOffspring(shared_ptr<AgableMob> target);
};
