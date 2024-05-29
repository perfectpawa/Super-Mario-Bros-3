#pragma once
#include "Goomba.h"
#include "AssetIDs.h"

#define PARA_GOOMBA_BBOX_WIDTH 20
#define PARA_GOOMBA_BBOX_HEIGHT 16

#define GOOMBA_STATE_FLY 10

class CParaGoomba : public CGoomba
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	bool haveWing = true;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);
	bool IsHaveWing() { return haveWing; }
	void BreakWing() { haveWing = false; }
};