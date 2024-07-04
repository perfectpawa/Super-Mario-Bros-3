#include "Brick.h"
#include "Animations.h"
#include "Sprites.h"

CBrick::CBrick(float x, float y, int type, int visualId)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->visualId = visualId;
}

void CBrick::Render()
{
	if (type == TYPE_BREAKABLE) {
		if (visualId == -1) {
			CAnimations::GetInstance()->Get(ID_ANI_BRICK_BREAKABLE)->Render(x, y);
		}
		return;
	}
	else if (type == TYPE_UNBREAKABLE) {
		if (visualId == -1) {
			CSprites::GetInstance()->Get(ID_SPRITE_BRICK_UNBREAKABLE)->Draw(x, y);
		}
		return;
	}
	CSprites::GetInstance()->Get(visualId)->Draw(x, y);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Breaking(bool canTakeButton)
{
	if(type == TYPE_BREAKABLE) {
		this->Delete();
	}
}