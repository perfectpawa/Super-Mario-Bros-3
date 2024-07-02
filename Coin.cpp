#include "Coin.h"
#include "debug.h"

void CCoin::Render()
{
	//if (!canInteract) return;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

//CoinEffect
CCoinEffect::CCoinEffect(float x, float y) : CGameObject(x, y)
{
	vy = -COIN_EFFECT_SPEED;
	maxPosy = y - 16*4;
	minPosy = y - 16*2;
}

void CCoinEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN_FAST)->Render(x, y);

	//RenderBoundingBox();
}

void CCoinEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if(y <= maxPosy)
	{
		vy = COIN_EFFECT_SPEED;
	}
	if (vy > 0 && y >= minPosy)
	{
		this->Delete();
		return;
	}
}

void CCoinEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
