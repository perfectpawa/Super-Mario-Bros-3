#include "Plant.h"
#include "Sprites.h"
#include "Animations.h"
#include "AssetIDs.h"

CPlant::CPlant(float x, float y, int height, int color) : CGameObject(x,y)
{
	this->height = height;
	this->color = color;

	this->plant_height = PLANT_PART_BBOX_HEIGHT * (height + 1);

	this->up_point = y - plant_height;
	this->down_point = y;

	this->player = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer());

	SetState(PLANT_STATE_IDLE);
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float playerX, playerY;
	player->GetPosition(playerX, playerY);
	float distance = abs(playerX - x);

	playerInLeft = (playerX < x);

	y += vy * dt;

	if(distance > PLANT_HIDE_RANGE && distance < PLANT_ATTACK_RANGE
		&& delay_start != -1 && GetTickCount64() - delay_start > PLANT_GROW_UP_DELAY)
	{
		SetState(PLANT_STATE_GROW_UP);
		delay_start = -1;
	}

	if (y < up_point) {
		y = up_point;
		SetState(PLANT_STATE_ATTACK);
	}

	if (y > down_point) {
		y = down_point;
		SetState(PLANT_STATE_IDLE);
	}

	CGameObject::Update(dt);
}

void CPlant::Render()
{
	int headId = ID_ANI_PLANT_HEAD + color * 100;
	CAnimations::GetInstance()->Get(headId)->Render(x, y, 0);

	float yy = y + PLANT_PART_BBOX_HEIGHT * 1.5f;
	for (int i = 1; i < height; i++)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_PLANT_BODY)->Draw(x, yy);
		yy += PLANT_PART_BBOX_HEIGHT;
	}

	//RenderBoundingBox();	
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLANT_BBOX_WIDTH / 2;
	r = l + PLANT_BBOX_WIDTH;
	
	t = y - PLANT_PART_BBOX_HEIGHT / 2;
	b = t + plant_height;
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_IDLE:
		vy = 0;
		if (delay_start == -1) delay_start = GetTickCount64();
		break;
	case PLANT_STATE_GROW_UP:
		vy = -PLANT_GROW_SPEED;
		break;
	case PLANT_STATE_ATTACK:
		Attack();
		break;
	case PLANT_STATE_GROW_DOWN:
		vy = PLANT_GROW_SPEED;
		break;
	}
}

void CPlant::Attack()
{
	if(attack_start == -1) attack_start = GetTickCount64();
	else if (GetTickCount64() - attack_start > PLANT_ATTACK_TIME)
	{
		attack_start = -1;
		SetState(PLANT_STATE_GROW_DOWN);
	}
}