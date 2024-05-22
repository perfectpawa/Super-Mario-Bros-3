#include "FallCheckingObject.h"
#include "Mario.h"

CFallCheckingObject::CFallCheckingObject(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GRAVITY;
	vx = -WALKING_SPEED;
}

void CFallCheckingObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - BBOX_WIDTH / 2;
	top = y - BBOX_HEIGHT / 2;
	right = left + BBOX_WIDTH;
	bottom = top + BBOX_HEIGHT;
}

void CFallCheckingObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFallCheckingObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CFallCheckingObject*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
}

void CFallCheckingObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFallCheckingObject::Render()
{
	RenderBoundingBox();
}
