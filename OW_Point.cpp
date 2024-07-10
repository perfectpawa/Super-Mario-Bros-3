#include "OW_Point.h"
#include "Animations.h"


COWPoint::COWPoint(float x, float y, bool canGoIn, int type) : COWGameObject(x, y, canGoIn)
{
	this->type = type;
}

void COWPoint::Render()
{
	if (type == OW_POINT_TYPE_LOCK_BIG_CASTLE) {
		CAnimations::GetInstance()->Get(ID_ANI_POINT_LOCK_BIG_CASTLE)->Render(x + 8, y - 8);
		return;
	}

	int spriteId = ID_SPRITE_POINT_START + type;
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}