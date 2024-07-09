#pragma once
#include "EffectObject.h"

#define BREAKING_EFFECT_SPEED 0.1f

class CBreakingEffect : public CEffectObject {
protected:
	float vy;
	float xOffset;
	float maxPosy;
	float minPosy;
public:
	CBreakingEffect(float x, float y);
	void Render();
	void Update(DWORD dt);
};