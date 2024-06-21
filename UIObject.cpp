#include "UIObject.h"
#include "Sprites.h"

CUIObject::CUIObject()
{
	x = y = 0;
	spriteID = -1;
}

CUIObject::~CUIObject()
{

}

void CUIObject::Render()
{
	CSprites::GetInstance()->Get(spriteID)->Draw(x, y);
}