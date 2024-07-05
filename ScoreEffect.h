#pragma once
#include "EffectObject.h"

#define EFFECT_SPEED 0.05f

class CScoreEffect : public CEffectObject {
protected:
	float vy;
	float minPosy;
	int score;
public:
	CScoreEffect(float x, float y, int score);
	void Render();
	void Update(DWORD dt);
};