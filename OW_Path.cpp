#include "OW_Path.h"

COWPath::COWPath(float x, float y, bool canGoIn, bool isPoint, bool isVertical, bool haveTurn) : COWGameObject(x, y, canGoIn)
{
	this->isVertical = isVertical;
	this->haveTurn = haveTurn;
	this->isPoint = isPoint;
}

void COWPath::Render()
{
	int spriteId = ID_SPRITE_OW_PATH_HORIZONTAL;
	
	if(isVertical) spriteId += 1;

	if (isPoint) spriteId += 100;

	if (haveTurn) spriteId = ID_SPRITE_OW_PATH_COIN_TURN;

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}