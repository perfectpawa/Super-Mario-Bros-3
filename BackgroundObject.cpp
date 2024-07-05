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
	this->player = dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer());
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

void CBackgroundObject::RenderInViewport(int spriteId, float x, float y)
{
	if(player->isInMarioViewPort(x))
		CSprites::GetInstance()->Get(spriteId)->Draw(x, y);


}

void CBackgroundObject::RenderCloud()
{
	RenderInViewport(ID_SPRITE_BACKGROUND_CLOUD_LEFT, x, y);

	float xx = x + 8;
	for (int i = 1; i <= length; i++) {
		RenderInViewport(ID_SPRITE_BACKGROUND_CLOUD_CENTER_LEFT, xx, y);
		xx += 8;
		RenderInViewport(ID_SPRITE_BACKGROUND_CLOUD_CENTER_RIGHT, xx, y);
		xx += 8;
	}
	RenderInViewport(ID_SPRITE_BACKGROUND_CLOUD_RIGHT, xx, y);
}

void CBackgroundObject::RenderGrass()
{
	RenderInViewport(ID_SPRITE_BACKGROUND_GRASS, x, y);
}

void CBackgroundObject::RenderBushSmall()
{
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 2, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 3, y);


	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 2, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 3, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 2, y - 16 * 2);
}

void CBackgroundObject::RenderBushBig1()
{
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 4, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 5, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 6, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 7, y);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 2, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 4, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x + 16 * 5, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 6, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 7, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 2, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 3, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 4, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 5, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 6, y - 16 * 2);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 2, y - 16 * 3);


}

void CBackgroundObject::RenderBushBig2() {
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 4, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 5, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 6, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 7, y);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 2, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 3, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 4, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 5, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 6, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 7, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 2, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 3, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 4, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 5, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 6, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 7, y - 16 * 2);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 4, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 5, y - 16 * 3);

}

void CBackgroundObject::RenderBushTall() {
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 4, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 5, y);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 4, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 5, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 4, y - 16 * 2);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 2, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 4, y - 16 * 3);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16, y - 16 * 4);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_LEFT, x + 16 * 2, y - 16 * 4);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16 * 4);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 4, y - 16 * 4);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x + 16 * 2, y - 16 * 5); 
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_CENTER, x + 16 * 3, y - 16 * 5);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_RIGHT, x + 16 * 4, y - 16 * 5); 

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_MID_LEFT, x + 16 * 2, y - 16 * 6);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_BOT_RIGHT, x + 16 * 3, y - 16 * 6);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 4, y - 16 * 6);

	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_LEFT, x + 16 * 2, y - 16 * 7);
	RenderInViewport(ID_SPRITE_BACKGROUND_BUSH_TOP_RIGHT, x + 16 * 3, y - 16 * 7);



}

void CBackgroundObject::RenderBlackBackground() {
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 26; j++) {
			RenderInViewport(ID_SPRITE_BLACK_BACKGROUND, x + 16 * i, y - 16 * j);
		}
	}
}

void CBackgroundObject::RenderBlackBackgroundBoundary() {
	for (int i = 0; i <length; i++) {
		RenderInViewport(ID_SPRITE_BLACK_BACKGROUND_BOUNDARY, x, y - 16 * i);
	}
}

void CBackgroundObject::RenderBlackBushSmall() {
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_LEFT, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT, x + 16 * 2, y);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT, x + 16 * 2, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT, x + 16 * 2, y - 16 * 2);
}

void CBackgroundObject::RenderBlackBushMedium() {
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT, x, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_LEFT, x + 16, y);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT, x + 16 * 4, y);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT, x + 16, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_RIGHT, x + 16 * 3, y - 16);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT, x + 16 * 4, y - 16);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT, x + 16, y - 16 * 2);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT, x + 16 * 3, y - 16 * 2);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT, x + 16, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_BOT_RIGHT, x + 16 * 2, y - 16 * 3);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT, x + 16 * 3, y - 16 * 3);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_LEFT, x + 16, y - 16 * 4);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_MID_RIGHT, x + 16 * 2, y - 16 * 4);

	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_LEFT, x + 16, y - 16 * 5);
	RenderInViewport(ID_SPRITE_BACKGROUND_BLACK_BUSH_TOP_RIGHT, x + 16 * 2, y - 16 * 5);

}