#pragma once
#include "EffectObject.h"

#define BREAKING_EFFECT_SPEED 0.15f
#define BREAKING_EFFECT_ACCELERATION 0.0005f


class CBreakingEffect : public CEffectObject {
protected:
	float vy;
	float ay;
	float xOffset;
	float maxPosy;
	float minPosy;
public:
	CBreakingEffect(float x, float y);
	void Render();
	void Update(DWORD dt);
};