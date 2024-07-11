#include "CardBlock.h"
#include "AssetIDs.h"

#include "Sprites.h"

CCardBlock::CCardBlock(float x, float y) : CGameObject(x, y)
{
	type = ID_SPRITE_CARD_TYPE_MUSHROOM;
	change_start = GetTickCount64();
	item_y = y;
	min_y = y - 32;
}

void CCardBlock::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if(hited && !geted)
	{
		item_y -= 0.1f * dt;
		if (item_y < min_y) {
			geted = true;
		}
	}

	if (!hited && GetTickCount64() - change_start > CHANGE_TIME)
	{
		type++;
		if (type > ID_SPRITE_CARD_TYPE_STAR)
			type = ID_SPRITE_CARD_TYPE_MUSHROOM;
		change_start = GetTickCount64();
	}
}

void CCardBlock::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_CARD_BLOCK_HOLDER)->Draw(x - 8, y - 8);
	CSprites::GetInstance()->Get(ID_SPRITE_CARD_BLOCK_HOLDER + 1)->Draw(x + 8, y - 8);
	CSprites::GetInstance()->Get(ID_SPRITE_CARD_BLOCK_HOLDER + 2)->Draw(x - 8, y + 8);
	CSprites::GetInstance()->Get(ID_SPRITE_CARD_BLOCK_HOLDER + 3)->Draw(x + 8, y + 8);

	if(!geted) CSprites::GetInstance()->Get(ID_SPRITE_CARD_BLOCK_ITEM + type)->Draw(x, item_y);
}

void CCardBlock::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - 8;
	t = y - 8;
	r = l + 16;
	b = t + 16;
}