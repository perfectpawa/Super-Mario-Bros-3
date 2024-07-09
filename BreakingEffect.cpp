#include "BreakingEffect.h"

CBreakingEffect::CBreakingEffect(float x, float y) : CEffectObject(x, y)
{
	vy = -BREAKING_EFFECT_SPEED;
	minPosy = y - 16;
	maxPosy = y + 8;
	xOffset = 0;
}

void CBreakingEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x + xOffset, y);
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x - xOffset, y);

	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x + xOffset/2, y - 8);
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_BREAK_BRICK)->Render(x - xOffset/2, y - 8);
}

void CBreakingEffect::Update(DWORD dt)
{
	y += vy * dt;
	xOffset += BREAKING_EFFECT_SPEED/2 * dt;

	if (y < minPosy) vy = -vy;
	if (y > maxPosy) {
		this->Delete();
	}
}