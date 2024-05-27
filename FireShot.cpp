#include "FireShot.h"
#include "debug.h"

CFireShot::CFireShot(float x, float y, float vx, float vy) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;

	this->vx = FIRE_SPEED * vx;
	this->vy = FIRE_SPEED * vy;
}

void CFireShot::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - BBOX_WIDTH / 2;
	top = y - BBOX_HEIGHT / 2;
	right = left + BBOX_WIDTH;
	bottom = top + BBOX_HEIGHT;
}

void CFireShot::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFireShot::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFireShot*>(e->obj)) return;
}

void CFireShot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFireShot::Render()
{
	int aniId = ID_VENUS_FIRE_BALL;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}