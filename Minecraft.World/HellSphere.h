#pragma once
using namespace std;

#include "Throwable.h"

class HitResult;

class HellSphere : public Throwable
{
public:
	eINSTANCEOF GetType() { return eTYPE_HELLSPHERE; }
	static Entity *create(Level *level) { return new HellSphere(level); }

private:
	void _init();
	void explode();

public:
	HellSphere(Level *level);
	HellSphere(Level *level, shared_ptr<LivingEntity> mob);
	HellSphere(Level *level, double x, double y, double z);

protected:
	virtual void onHit(HitResult *res);
};
