#include "CoinEffect.h"
#include "AssetIDs.h"
#include "Animations.h"


CCoinEffect::CCoinEffect(float x, float y) : CEffectObject(x, y)
{
	vy = -COIN_EFFECT_SPEED;
	maxPosy = y - 16 * 4;
	minPosy = y - 16 * 2;
}

void CCoinEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN_FAST)->Render(x, y);

}

void CCoinEffect::Update(DWORD dt)
{
	y += vy * dt;

	if (y <= maxPosy)
	{
		vy = COIN_EFFECT_SPEED;
	}
	if (vy > 0 && y >= minPosy)
	{
		this->Delete();
		return;
	}
}

