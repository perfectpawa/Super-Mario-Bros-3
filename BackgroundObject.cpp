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
	case TYPE_BUSH_SMALL:
		RenderBushSmall();
		break;
	case TYPE_BUSH_BIG_1:
		RenderBushBig1();
		break;
	case TYPE_BUSH_BIG_2:
		RenderBushBig2();
		break;
	case TYPE_BUSH_TALL:
		RenderBushTall();
		break;
	case TYPE_BLACK_BACKGROUND:
		RenderBlackBackground();
		break;
	case TYPE_BLACK_BACKGROUND_BOUNDARY:
		RenderBlackBackgroundBoundary();
		break;
	case TYPE_BLACK_BUSH_SMALL:
		RenderBlackBushSmall();
		break;
	case TYPE_BLACK_BUSH_MEDIUM:
		RenderBlackBushMedium();
		break;
	}
}

void CBackgroundObject::RenderCloud()
{
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

void CBackgroundObject::RenderBushSmall()
{
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y); 
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 3, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 2, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 3, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 2, y - 16 * 2);
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

void CBackgroundObject::RenderBushBig2() {
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 4, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 5, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 6, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 7, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 2, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 3, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 4, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 5, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 6, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 7, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 2, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 3, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 4, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 5, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 6, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 7, y - 16 * 2);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 4, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 5, y - 16 * 3);

}

void CBackgroundObject::RenderBushTall() {
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 4, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 5, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 4, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 5, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y - 16 * 2);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 2, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y - 16 * 3);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 4);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT)->Draw(x + 16 * 2, y - 16 * 4);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16 * 4);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y - 16 * 4);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x + 16 * 2, y - 16 * 5); 
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_CENTER)->Draw(x + 16 * 3, y - 16 * 5);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y - 16 * 5); 

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT)->Draw(x + 16 * 2, y - 16 * 6);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT)->Draw(x + 16 * 3, y - 16 * 6);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 4, y - 16 * 6);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT)->Draw(x + 16 * 2, y - 16 * 7);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT)->Draw(x + 16 * 3, y - 16 * 7);



}

void CBackgroundObject::RenderBlackBackground() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 26; j++) {
			CSprites::GetInstance()->Get(ID_SPRITE_BLACK_BACKGROUND)->Draw(x + 16 * i, y - 16 * j);
		}
	}
}

void CBackgroundObject::RenderBlackBackgroundBoundary() {
	for (int i = 0; i <length; i++) {
		CSprites::GetInstance()->Get(ID_SPRITE_BLACK_BACKGROUND_BOUNDARY)->Draw(x, y - 16 * i);
	}
}

void CBackgroundObject::RenderBlackBushSmall() {
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_LEFT)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT)->Draw(x + 16 * 2, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT)->Draw(x + 16 * 2, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT)->Draw(x + 16 * 2, y - 16 * 2);
}

void CBackgroundObject::RenderBlackBushMedium() {
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_LEFT)->Draw(x + 16, y);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT)->Draw(x + 16 * 4, y);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT)->Draw(x + 16, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_RIGHT)->Draw(x + 16 * 3, y - 16);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT)->Draw(x + 16 * 4, y - 16);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT)->Draw(x + 16, y - 16 * 2);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT)->Draw(x + 16 * 3, y - 16 * 2);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT)->Draw(x + 16, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_RIGHT)->Draw(x + 16 * 2, y - 16 * 3);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT)->Draw(x + 16 * 3, y - 16 * 3);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT)->Draw(x + 16, y - 16 * 4);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT)->Draw(x + 16 * 2, y - 16 * 4);

	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT)->Draw(x + 16, y - 16 * 5);
	CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT)->Draw(x + 16 * 2, y - 16 * 5);

}