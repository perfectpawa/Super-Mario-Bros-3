#include "CharacterIconUI.h"
#include "Sprites.h"
#include "AssetIDs.h"

CCharacterIconUI::CCharacterIconUI(float x, float y, int type) : CIconUI(x, y, iconID = -1, haveAni = false)
{
	this->type = type;
}

void CCharacterIconUI::Render()
{
	int spriteID = ID_SPRITE_UI_MARIO_ICON + type;
	CSprites::GetInstance()->Get(spriteID)->Draw(x, y);
}