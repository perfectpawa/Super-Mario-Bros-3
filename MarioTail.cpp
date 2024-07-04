#include "MarioTail.h"

#include "Goomba.h"
#include "ParaGoomba.h"
#include "Koopas.h"
#include "Brick.h"
#include "BrickCoin.h"

#include "debug.h"

CMarioTail::CMarioTail()
{
}

void CMarioTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMarioTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0) return;

	if(dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		goomba->TakeDamage();
	}
	else if(dynamic_cast<CParaGoomba*>(e->obj))
	{
		CParaGoomba* goomba = dynamic_cast<CParaGoomba*>(e->obj);
		goomba->TakeDamage();
	}
	if(dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		koopas->TakeDamage();
	}

	if(dynamic_cast<CBrickCoin*>(e->obj))
	{
		CBrickCoin* brick = dynamic_cast<CBrickCoin*>(e->obj);
		brick->Breaking(false);
	}
	else
	if(dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		brick->Breaking();
	}

}

void CMarioTail::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void CMarioTail::Render()
{
	//RenderBoundingBox();
}

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_TAIL_BBOX_WIDTH / 2;
	top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
	right = left + MARIO_TAIL_BBOX_WIDTH;
	bottom = top + MARIO_TAIL_BBOX_HEIGHT;
}