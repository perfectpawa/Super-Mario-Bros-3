#include "Leaf.h"
#include "debug.h"
#include "Mario.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = LEAF_SWING_ACCELERATION;
	this->ay = LEAF_GRAVITY;

	this->vx = -LEAF_SWING_MAX_SPEED;
	this->vy = -LEAF_STARTUP_BOOST;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if(vy > LEAF_MAX_FALL_SPEED)
	{
		vy = LEAF_MAX_FALL_SPEED;
		ay = 0;
	}

	if (abs(vx) > LEAF_SWING_MAX_SPEED)
	{
		ax = -ax;
	}

	if (y > MAX_Y)
	{
		Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_LEAF)->Render(x, y);
	//RenderBoundingBox();
}

