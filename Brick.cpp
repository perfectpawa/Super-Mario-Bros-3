#include "Brick.h"
#include "Animations.h"
#include "Sprites.h"

CBrick::CBrick(float x, float y, int type, int spriteId)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->spriteId = spriteId;
}

void CBrick::Render()
{
	if (type == TYPE_BREAKABLE) {
		if (spriteId == -1) {
			spriteId = ID_SPRITE_BRICK_BREAKABLE;
		}
	}
	else if (type == TYPE_UNBREAKABLE) {
		if (spriteId == -1) {
			spriteId = ID_SPRITE_BRICK_UNBREAKABLE;
		}
	}

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}