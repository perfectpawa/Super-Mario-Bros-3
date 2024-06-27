#include "OW_MapHolder.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"

COWMapHolder::COWMapHolder(float x, float y, int width, int height, int bgColor)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	switch (bgColor)
	{
	case BG_YELLOW:
		this->idTextureBG = 8891;
		break;
	default:
		this->idTextureBG = 8891;
		break;
	}
}

void COWMapHolder::Render()
{
	DrawBG();
	DrawBorder();
}

void COWMapHolder::DrawBG()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(idTextureBG);

	rect.left = 0;
	rect.top = 0;
	rect.right = this->width * 16;
	rect.bottom = this->height * 16;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - 8 + rect.right / 2;
	float yy = y - 8 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, 1.0f, rect.right - 1, rect.bottom - 1);
}

void COWMapHolder::DrawBorder()
{
	float xx = x - 8 - 4;
	float yy = y - 8 - 4;

	CSprites* s = CSprites::GetInstance();

	// Top
	s->Get(ID_SPRITE_OW_BORDER_TOP_LEFT)->Draw(xx, yy);
	for (int i = 1; i < (width + 1) * 2; i++) {
		s->Get(ID_SPRITE_OW_BORDER_TOP_CENTER)->Draw(xx + i * 8, yy);
	}
	s->Get(ID_SPRITE_OW_BORDER_TOP_RIGHT)->Draw(xx + 29 * 8, yy);

	//Center
	for (int i = 1; i < (height + 1) * 2 - 1; i++) {
		s->Get(ID_SPRITE_OW_BORDER_MID_LEFT)->Draw(xx, yy + i * 8);
		s->Get(ID_SPRITE_OW_BORDER_MID_RIGHT)->Draw(xx + 29 * 8, yy + i * 8);
	}

	//Down
	s->Get(ID_SPRITE_OW_BORDER_DOWN_LEFT)->Draw(xx, yy + 21 * 8);
	for (int i = 1; i < (width + 1) * 2; i++) {
		s->Get(ID_SPRITE_OW_BORDER_DOWN_CENTER)->Draw(xx + i * 8, yy + 21 * 8);
	}
	s->Get(ID_SPRITE_OW_BORDER_DOWN_RIGHT)->Draw(xx + 29 * 8, yy + 21 * 8);

}