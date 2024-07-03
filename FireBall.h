#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8

#define FIREBALL_SPEED 0.1f

#define FIREBALL_EXIST_TIME 5000


class CFireBall : public CGameObject
{
protected:
	ULONGLONG exist_start;
public:
	CFireBall(float x, float y, float vx, float vy);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};