#include "BackgroundObject.h"
#include "Sprites.h"
#include "AssetIDs.h"
#include "debug.h"

CBackgroundObject::CBackgroundObject(float x, float y, int type, int length)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->length = length;
}

void CBackgroundObject::Render()
{
	switch (type)
	{
	case TYPE_CLOUD:
		RenderCloud();
		break;
	case TYPE_GRASS:
		RenderGrass();
		break;
	case TYPE_BUSH_BIG_1:
		RenderBushBig1();
		break;
	
	}
}

void CBackgroundObject::RenderCloud()
{
	//debugout length
	DebugOut(L"length: %d\n", length);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_CLOUD_LEFT)->Draw(x, y);
	float xx = x + 8;
	for (int i = 1; i <= length; i++) {
		CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_CLOUD_CENTER_LEFT)->Draw(xx, y);
		xx += 8;
		CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_CLOUD_CENTER_RIGHT)->Draw(xx, y);
		xx += 8;
	}
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_CLOUD_RIGHT)->Draw(xx, y);
}

void CBackgroundObject::RenderGrass()
{
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_GRASS)->Draw(x, y);
}

void CBackgroundObject::RenderBushBig1()
{
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 4, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 5, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 6, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 7, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 2, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x + 16 * 5, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 6, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 7, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 2, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 3, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 4, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 5, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 6, y - 16 * 2);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 2, y - 16 * 3);


}