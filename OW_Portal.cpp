#include "OW_Portal.h"

COWPortal::COWPortal(float x, float y, bool canGoIn, int portalId) : COWGameObject(x, y, canGoIn)
{
	portalSpriteId = 88886000 + portalId;

	switch (portalId)
	{
	case 1:
		sceneId = 10;
		break;

	default:
		sceneId = -1;
		break;
	}
}

void COWPortal::Render()
{
	CSprites::GetInstance()->Get(portalSpriteId)->Draw(x, y);
}