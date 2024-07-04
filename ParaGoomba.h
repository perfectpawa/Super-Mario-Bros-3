#pragma once
#include "Goomba.h"
#include "AssetIDs.h"

#define PARA_GOOMBA_BBOX_WIDTH 20
#define PARA_GOOMBA_BBOX_HEIGHT 20

#define PARA_GOOMBA_GRAVITY 0.001f

#define PARA_GOOMBA_HOP_SPEED 0.15f
#define PARA_GOOMBA_FLY_SPEED 0.3f

#define PARA_GOOMBA_WALK_TIMEOUT 1000


#define GOOMBA_STATE_HOPPING 300
#define GOOMBA_STATE_FLYING 400


class CParaGoomba : public CGoomba
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	bool haveWing = true;
	int hopCount = 0;

	LPGAMEOBJECT player = NULL;


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
	bool IsHaveWing() const { return haveWing; }
	void BreakWing() { haveWing = false; }
	virtual void TakeDamage();
};