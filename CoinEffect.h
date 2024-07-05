#pragma once
#include "EffectObject.h"
#include "ScoreEffect.h"

#define COIN_EFFECT_SPEED 0.2f

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