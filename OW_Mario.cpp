#include "OW_Mario.h"
#include "debug.h"
#include "Animations.h"

COWMario::COWMario(float x, float y, bool canGoIn) : COWGameObject(x, y, canGoIn)
{
	start_x = x;
	start_y = y;
	end_x = x;
	end_y = y;
	
	isMoving = false;
	wantMove = false;

	moveHorizontal = 0;
	moveVertical = 0;

	DebugOut(L"[INFO] OW_Mario created!\n");
}

void COWMario::Update(DWORD dt, vector<COWGameObject*>* coObjects)
{
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
	DebugOut(L"[INFO] OW_Mario moving!\n");
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
	DebugOut(L"[INFO] OW_Mario getting destination!\n");
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
}