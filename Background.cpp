#include "Background.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CBackground::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x, y);
}

void CBackground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 1;
	t = y - 1;
	r = x + 1;
	b = y + 1;
}