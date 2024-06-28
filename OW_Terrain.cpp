#include "OW_Terrain.h"
#include "Animations.h"

COWTerrain::COWTerrain(float x, float y, bool canGoIn, int type, int sub_type) : COWGameObject(x, y, canGoIn)
{
	this->type = type;
	this->sub_type = sub_type;
}

void COWTerrain::Render()
{
	switch (type)
	{
	case OW_TERRAIN_TYPE_GRASS:
		CAnimations::GetInstance()->Get(ID_ANI_OW_TERRAIN_GRASS)->Render(x, y);
		break;
	case OW_TERRAIN_TYPE_ROCK:
		CSprites::GetInstance()->Get(ID_SPRITE_OW_TERRAIN_ROCK)->Draw(x, y);
		break;
	case OW_TERRAIN_TYPE_WATER:
		CSprites::GetInstance()->Get(ID_SPRITE_OW_TERRAIN_WATER_BASE + sub_type)->Draw(x, y);
		break;
	default:
		break;
	}

}