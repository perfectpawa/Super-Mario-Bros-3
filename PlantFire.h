#pragma once
#include "Plant.h"

class CPlantFire : public CPlant
{
protected:
	bool aimVertical;
	bool isAttacking;
public:
	CPlantFire(float x, float y, int height = 2);
	virtual void Render();
	virtual void Attack();
};