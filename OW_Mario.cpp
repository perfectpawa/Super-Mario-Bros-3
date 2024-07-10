#include "OW_Mario.h"
#include "debug.h"
#include "Animations.h"
#include "OW_Portal.h"
#include "OW_Path.h"

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

		if (dir_x > 0) {
			if(x > end_x) x = end_x;
		}
		else {
			if(x < end_x) x = end_x;
		}

		if (dir_y > 0) {
			if(y > end_y) y = end_y;
		}
		else {
			if(y < end_y) y = end_y;
		}

		if (x == end_x && y == end_y)
		{
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
		GetMoveDestination(coObjects);
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
	x += moveHorizontal * MOVE_SPEED * dt;
	y += moveVertical * MOVE_SPEED * dt;

	//debug out x,y, end_x, end_y
	DebugOut(L"[INFO] x: %f, y: %f, end_x: %f, end_y: %f\n", x, y, end_x, end_y);

	if (moveHorizontal > 0) {
		if (x > end_x) x = end_x;
	}
	else {
		if (x < end_x) x = end_x;
	}

	if (moveVertical > 0) {
		if (y > end_y) y = end_y;
	}
	else{
		if (y < end_y) y = end_y;
	}

	if (x == end_x && y == end_y)
		isMoving = false;
}

void COWMario::GetMoveDestination(vector<COWGameObject*>* coObjects)
{
	start_x = x;
	start_y = y;

	end_x = x;
	end_y = y;

	COWGameObject* obj = nullptr;
	for (int i = 0; i < coObjects->size(); i++) {
		end_x += moveHorizontal * 16;
		end_y += moveVertical * 16;

		if (CheckValid(end_x, end_y, coObjects, obj)) {
			if (dynamic_cast<COWPath*>(obj) 
				&& !dynamic_cast<COWPath*>(obj)->CanGoIn()) {
				continue;
			}

			if (obj->CanGoIn()) {
				portalId = ((COWPortal*)obj)->GetSceneId();
				break;
			}

		}
		else {
			if(obj != nullptr 
				&& dynamic_cast<COWPath*>(obj)
				&& !dynamic_cast<COWPath*>(obj)->CanGoIn()
				) {
				end_x = start_x;
				end_y = start_y;
				break;
			}

			end_x -= moveHorizontal * 16;
			end_y -= moveVertical * 16;
			break;
		}
	}
	wantMove = false;

	if(end_x == x && end_y == y) return;

	isMoving = true;
}

bool COWMario::CheckValid(float x, float y, vector<COWGameObject*>* coObjects, COWGameObject*& obj)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		float co_x, co_y;
		(*coObjects)[i]->GetPosition(co_x, co_y);

		if (x == co_x && y == co_y) {
			obj = (*coObjects)[i];
			return true;
		}
	}
	return false;
}


void COWMario::GetInLevel()
{
	if (isMoving) return;
	if (portalId == -1) return;

	SaveFile::GetInstance()->SetLastStand(x, y);

	CGame::GetInstance()->InitiateSwitchScene(portalId);

}