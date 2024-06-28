#include "IconUI.h"
#include "Sprites.h"
#include "Animations.h"

CIconUI::CIconUI(float x, float y, int iconID, bool haveAni) : CUIObject(x, y)
{
	this->iconID = iconID;
	this->haveAni = haveAni;
}

void CIconUI::Render()
{
	if(haveAni)
		CAnimations::GetInstance()->Get(iconID)->Render(x, y);
	else
		CSprites::GetInstance()->Get(iconID)->Draw(x, y);
}