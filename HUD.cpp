#include "HUD.h"
#include "Sprites.h"

CHUD::CHUD(float x, float y) : CUIObject(x, y)
{
}

void CHUD::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_UI_HUD_HOLDER)->Draw(x + 16 * 2 + 1, y + 14);
	CSprites::GetInstance()->Get(ID_SPRITE_UI_MAIN_HUD)->Draw(x, y);
	CSprites::GetInstance()->Get(ID_SPRITE_UI_POWER_HUD_EMPTY)->Draw(x + 16 * 6, y);
	CSprites::GetInstance()->Get(ID_SPRITE_UI_POWER_HUD_EMPTY)->Draw(x + 16 * 7.5, y);
	CSprites::GetInstance()->Get(ID_SPRITE_UI_POWER_HUD_EMPTY)->Draw(x + 16 * 9, y);
}