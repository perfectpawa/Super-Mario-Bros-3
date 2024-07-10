#include "OW_Path.h"

COWPath::COWPath(float x, float y, bool canGoIn, bool isVertical, bool haveTurn) : COWGameObject(x, y, canGoIn)
{
	this->isVertical = isVertical;
	this->haveTurn = haveTurn;
}

void COWPath::Render()
{
	int spriteId = ID_SPRITE_OW_PATH_HORIZONTAL;
	
	if(isVertical) spriteId += 1;

	if (canGoIn) spriteId += 100;

	if (haveTurn) spriteId = ID_SPRITE_OW_PATH_COIN_TURN;

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}