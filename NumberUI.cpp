#include "NumberUI.h"
#include "Sprites.h"
#include "AssetIDs.h"

CNumberUI::CNumberUI(float x, float y, int number, int digit) : CUIObject(x, y)
{
	this->number = number;
	this->digit = digit;
}

void CNumberUI::Render()
{
	int temp = number;
	int count = 0;
	while (temp > 0)
	{
		int digit = temp % 10;
		temp /= 10;
		CSprites::GetInstance()->Get(ID_SPRITE_NUMBER_UI + digit)->Draw(x - 8 * count, y);
		count++;
	}

	if (count < digit)
	{
		for (int i = count; i < digit; i++)
		{
			CSprites::GetInstance()->Get(ID_SPRITE_NUMBER_UI)->Draw(x - 8 * i, y);
		}
	}
}