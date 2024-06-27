#include "OW_Path.h"
#include "debug.h"

COWPath::COWPath(float x, float y, bool canGoIn, bool isVertical, bool haveCoin, bool haveTurn) : COWGameObject(x, y, canGoIn)
{
	this->isVertical = isVertical;
	this->haveCoin = haveCoin;
	this->haveTurn = haveTurn;
	DebugOut(L"[INFO] OW_Path created!\n");
}

void COWPath::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_OW_PATH_HORIZONTAL;
	
	if(isVertical) aniId += 1;

	if (haveCoin) aniId += 100;

	if (haveTurn) aniId = ID_ANI_OW_PATH_COIN_TURN;

	animations->Get(aniId)->Render(x, y);
}