#include "ParaGoomba.h"
#include "Mario.h"

CParaGoomba::CParaGoomba(float x, float y) :CGoomba(x, y)
{
	this->ax = 0;
	this->ay = PARA_GOOMBA_GRAVITY;
	this->player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();

	this->die_start = -1;
	this->walk_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (haveWing) {
		if (state == GOOMBA_STATE_WALKING)
		{
			if (GetTickCount64() - walk_start > PARA_GOOMBA_WALK_TIMEOUT) {
				SetState(GOOMBA_STATE_HOPPING);
			}
			else {
				//if player is behind, go back
				float playerX, playerY;
				player->GetPosition(playerX, playerY);
				if(vx * (playerX - x) < 0)
				{
					vx = -vx;
				}
			}
		}
		else if (state == GOOMBA_STATE_HOPPING) {
			if (vy == 0) {
				vy = -PARA_GOOMBA_HOP_SPEED;
				hopCount++;
			}
			if (hopCount == 3) {
				hopCount = 0;
				SetState(GOOMBA_STATE_FLYING);
			}
		}
		else if (state == GOOMBA_STATE_FLYING && vy == 0) {
			SetState(GOOMBA_STATE_WALKING);
		}
	}

	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARA_GOOMBA_WALKING;

	if (haveWing) {
		aniId = ID_ANI_PARA_GOOMBA_WALKING_WITH_WING;
		if(state == GOOMBA_STATE_HOPPING)
		{
			aniId = ID_ANI_PARA_GOOMBA_HOPPING;
		}
		if(state == GOOMBA_STATE_FLYING)
		{
			aniId = ID_ANI_PARA_GOOMBA_FLYING;
		}
	}

	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARA_GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		vy = 0;
		walk_start = GetTickCount64();
		break;
	case GOOMBA_STATE_HOPPING:
		hopCount = 0;
		break;
	case GOOMBA_STATE_FLYING:
		vy = -PARA_GOOMBA_FLY_SPEED;
		break;
	}
}

void CParaGoomba::TakeDamage()
{
	if (haveWing) {
		BreakWing();
	}else
	{
		CGoomba::TakeDamage();
	}
}