#include "PlantFire.h"
#include "Sprites.h"
#include "AssetIDs.h"
#include "FireBall.h"

CPlantFire::CPlantFire(float x, float y, int height) : CPlant(x, y, height, PLANT_COLOR_RED)
{
	aimVertical = true;
	isAttacking = false;
}

void CPlantFire::Render()
{
	int headId = ID_SPRITE_PLANT_FIRE_HEAD_UP_LEFT;
	if (!aimVertical) headId += 1000;
	if (isAttacking) headId += 100;

	if(!playerInLeft) headId += 10;

	CSprites::GetInstance()->Get(headId)->Draw(x, y); 

	int yy = y + PLANT_PART_BBOX_HEIGHT * 1.5;
	for (int i = 1; i < height; i++)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_PLANT_BODY)->Draw(x, yy);
		yy += PLANT_PART_BBOX_HEIGHT;
	}
}

void CPlantFire::Attack()
{
	if (attack_start != -1 && GetTickCount64() - attack_start < PLANT_ATTACK_TIME / 2) {
		float playerX, playerY;
		player->GetPosition(playerX, playerY);
		aimVertical = (playerY < y);
	}else if (attack_start != -1 && GetTickCount64() - attack_start < PLANT_ATTACK_TIME) {
		isAttacking = true;
	}
	else if (attack_start != -1 && GetTickCount64() - attack_start > PLANT_ATTACK_TIME) {
		isAttacking = false;

		float playerX, playerY;
		player->GetPosition(playerX, playerY);

		float mx = playerX - x;
		float my = playerY - y;
		float length = sqrt(mx * mx + my * my);
		mx /= length;
		my /= length;

		float xx = x;
		if (playerInLeft) xx -= 2;
		else xx += 2;

		CGame::GetInstance()->GetCurrentScene()->AddObject(new CFireBall(xx, y, mx, my), OBJECT_TYPE_ATTACK);
	}

	CPlant::Attack();
}

