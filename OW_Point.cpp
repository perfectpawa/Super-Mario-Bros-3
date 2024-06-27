#include "OW_Point.h"
#include "debug.h"

COWPoint::COWPoint(float x, float y, bool canGoIn, int type) : COWGameObject(x, y, canGoIn)
{
	this->type = type;
}

void COWPoint::Render()
{
	int spriteId = ID_SPRITE_POINT_START + type;
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}