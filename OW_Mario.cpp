#include "OW_Mario.h"
#include "debug.h"
#include "Animations.h"
#include "OW_Portal.h"

COWMario::COWMario(float x, float y, bool canGoIn) : COWGameObject(x, y, canGoIn)
{
	start_x = x;
	start_y = y;
	end_x = x;
	end_y = y;
	
	isMoving = false;
	wantMove = false;
	isTravel = false;

	moveHorizontal = 0;
	moveVertical = 0;

	portalId = -1;

	DebugOut(L"[INFO] OW_Mario created!\n");
}

void COWMario::Update(DWORD dt, vector<COWGameObject*>* coObjects)
{
	if(isTravel)
	{
		//check dir beween start and end
		float dir_x = end_x - start_x;
		float dir_y = end_y - start_y;
		//normalize dir
		float len = sqrt(dir_x * dir_x + dir_y * dir_y);
		dir_x /= len;
		dir_y /= len;

		x += dir_x * MOVE_SPEED * dt;
		y += dir_y * MOVE_SPEED * dt;

		if(round(x) == round(end_x) && round(y) == round(end_y))
		{
			x = end_x;
			y = end_y;
			isTravel = false;
		}

		return;
	}

	if(isMoving)
	{
		Moving(dt);
	}
	else if (wantMove)
	{
		GetMovDestination(coObjects);
	}
}

void COWMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_OW_MARIO_SMALL;

	animations->Get(aniId)->Render(x, y);
}

void COWMario::Moving(DWORD dt)
{
	if(moveHorizontal == 1)
	{
		x += MOVE_SPEED * dt;
		if (x >= end_x)
		{
			x = end_x;
			isMoving = false;
		}
	}
	else if (moveHorizontal == -1)
	{
		x -= MOVE_SPEED * dt;
		if (x <= end_x)
		{
			x = end_x;
			isMoving = false;
		}
	}
	else if (moveVertical == 1)
	{
		y += MOVE_SPEED * dt;
		if (y >= end_y)
		{
			y = end_y;
			isMoving = false;
		}
	}
	else if (moveVertical == -1)
	{
		y -= MOVE_SPEED * dt;
		if (y <= end_y)
		{
			y = end_y;
			isMoving = false;
		}
	}
}

void COWMario::GetMovDestination(vector<COWGameObject*>* coObjects)
{
	if (moveHorizontal == 1)
	{
		end_x = x + 16;
	}
	else if (moveHorizontal == -1)
	{
		end_x = x - 16;
	}
	else if (moveVertical == 1)
	{
		end_y = y + 16;
	}
	else if (moveVertical == -1)
	{
		end_y = y - 16;
	}
	isMoving = true;
	wantMove = false;

	CheckEndPointValid(coObjects);
}

void COWMario::CheckEndPointValid(vector<COWGameObject*>* coObjects)
{
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		float pos_x, pos_y;
		coObjects->at(i)->GetPosition(pos_x, pos_y);

		if (end_x == pos_x && end_y == pos_y) {
			COWPortal* portal = dynamic_cast<COWPortal*>(coObjects->at(i));

			if (portal != NULL)
			{
				portalId = portal->GetSceneId();
			}else{
				portalId = -1;
			}
			return;
		}
	}

	end_x = x;
	end_y = y;
	isMoving = false;
}

void COWMario::GetInLevel()
{
	if (isMoving) return;
	if (portalId == -1) return;

	SaveFile::GetInstance()->SetLastStand(x, y);

	CGame::GetInstance()->InitiateSwitchScene(portalId);

}