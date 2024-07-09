#include "BreakingEffect.h"

CBreakingEffect::CBreakingEffect(float x, float y) : CEffectObject(x, y)
{
	vy = -BREAKING_EFFECT_SPEED;
	ay = BREAKING_EFFECT_ACCELERATION;
	minPosy = y - 32;
	maxPosy = y + 80;
	xOffset = 0;
}

void CBreakingEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x + xOffset, y);
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x - xOffset, y);

	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x + xOffset/1.5f, y - 16);
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x - xOffset/1.5f, y - 16);
}

void CBreakingEffect::Update(DWORD dt)
{
	vy += ay * dt;
	y += vy * dt;
	xOffset += BREAKING_EFFECT_SPEED/2 * dt;

	if (y > maxPosy) {
		this->Delete();
	}
}