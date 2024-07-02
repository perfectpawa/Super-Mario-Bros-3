#pragma once
#include "EffectObject.h"

#define COIN_EFFECT_SPEED 0.3f

class CCoinEffect : public CEffectObject {
protected:
	float vy;
	float maxPosy;
	float minPosy;
public:
	CCoinEffect(float x, float y);
	void Render();
	void Update(DWORD dt);
};