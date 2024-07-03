#include "FireBall.h"
#include "AssetIDs.h"
#include "Animations.h"

CFireBall::CFireBall(float x, float y, float vx, float vy) : CGameObject(x, y)
{
	this->vx = vx * FIREBALL_SPEED;
	this->vy = vy * FIREBALL_SPEED;

	this->exist_start = GetTickCount64();
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (GetTickCount64() - exist_start > FIREBALL_EXIST_TIME)
	{
		this->Delete();
		return;
	}

	x += vx * dt;
	y += vy * dt;

	CGameObject::Update(dt, coObjects);
}

void CFireBall::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIRE_BALL)->Render(x, y);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_BBOX_WIDTH;
	b = y + FIREBALL_BBOX_HEIGHT;
}