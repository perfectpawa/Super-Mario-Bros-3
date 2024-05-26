#include "Mushroom.h"
#include "debug.h"
#include "Mario.h"

CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->start_y = y - 16;
	SetState(MUSHROOM_STATE_IDLE);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if(state == MUSHROOM_STATE_IDLE)
	{
		float posx, posy;
		GetPosition(posx, posy);
		if (posy <= start_y)
		{
			SetState(MUSHROOM_STATE_WALKING);
		}
	}
}


void CMushroom::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		this->ay = -MUSHROOM_GRAVITY/5;
		break;
	case MUSHROOM_STATE_WALKING:
		this->ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_WALKING_SPEED;
		break;
	}
}
