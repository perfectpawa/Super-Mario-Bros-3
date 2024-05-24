#include "Venus.h"

CVenus::CVenus(float x, float y) :CGameObject(x, y)
{
	this->ay = -VENUS_GROW_SPEED;
}

void CVenus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = left + VENUS_BBOX_WIDTH;
	bottom = top + VENUS_BBOX_HEIGHT;
}


void CVenus::OnNoCollision(DWORD dt)
{

};

void CVenus::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CVenus::Render()
{
	RenderBoundingBox();
}

void CVenus::SetState(int state)
{
	/*CGameObject::SetState(state);
	switch (state)
	{

	}*/
}
