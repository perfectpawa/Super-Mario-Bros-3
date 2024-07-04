#pragma once
#include "GameObject.h"

#define ID_SPRITE_CARD_TYPE_MUSHROOM 1
#define ID_SPRITE_CARD_TYPE_FLOWER 2
#define ID_SPRITE_CARD_TYPE_STAR 3

#define CHANGE_TIME 200

class CCardBlock : public CGameObject
{
protected:
	int type;
	bool hited = false;
	bool geted = false;
	float item_y;
	float min_y;
	ULONGLONG change_start;
public:
	CCardBlock(float x, float y);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Hit() { hited = true; }
};