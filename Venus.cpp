#include "Venus.h"
#include "FireShot.h"
#include "Mario.h"
#include "debug.h"

CVenus::CVenus(float x, float y) : CGameObject(x, y)
{
	this->player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	this->idleTime = 0;
	this->aimTime = 0;
	this->fireTime = 0;
	this->idlePosY = y;
	this->firePosY = y - VENUS_BBOX_HEIGHT + 9;

	this->SetState(VENUS_STATE_IDLE);
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
	y += vy * dt;
};

void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);


	float playerX, playerY, length = 0;
	player->GetPosition(playerX, playerY);

	mx = playerX - x;
	my = playerY - y;
	length = sqrt(mx * mx + my * my);
	mx /= length;
	my /= length;

	if (canGrowUp && state == VENUS_STATE_IDLE && length < VENUS_ATK_RANGE && GetTickCount64() - idleTime > VENUS_IDLE_TIME) {
		SetState(VENUS_STATE_GROW_UP);
	}
	else if (state == VENUS_STATE_GROW_UP && y <= firePosY)
	{
		SetState(VENUS_STATE_AIM);
	}
	else if (state == VENUS_STATE_AIM && GetTickCount64() - aimTime > VENUS_AIM_TIME)
	{
		SetState(VENUS_STATE_FIRE);
		CFireShot* fire = new CFireShot(x, y - 8, mx, my);
		CGame::GetInstance()->GetCurrentScene()->AddObject(fire, OBJECT_TYPE_VENUS_FIRE_BALL);
	}
	else if (state == VENUS_STATE_FIRE && GetTickCount64() - fireTime > VENUS_FIRE_TIME)
	{
		SetState(VENUS_STATE_GROW_DOWN);
	}
	else if (state == VENUS_STATE_GROW_DOWN && y >= idlePosY)
	{
		SetState(VENUS_STATE_IDLE);
	}
}


void CVenus::Render()
{
	int aniId = ID_VENUS_IDLE_LEFT;

	if(mx > 0)
		aniId = ID_VENUS_IDLE_RIGHT;
	else 
		aniId = ID_VENUS_IDLE_LEFT;

	if (state == VENUS_STATE_FIRE) {
		if(mx > 0)
			aniId = ID_VENUS_FIRE_RIGHT;
		else
			aniId = ID_VENUS_FIRE_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CVenus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_IDLE:
		vy = 0;
		idleTime = GetTickCount64();
		break;
	case VENUS_STATE_GROW_UP:
		vy = -VENUS_GROW_SPEED;
		break;
	case VENUS_STATE_AIM:
		vy = 0;
		aimTime = GetTickCount64();
		break;
	case VENUS_STATE_FIRE:
		fireTime = GetTickCount64();
		break;
	case VENUS_STATE_GROW_DOWN:
		vy = VENUS_GROW_SPEED;
		break;
	}
}

