#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define VENUS_BBOX_WIDTH 15
#define VENUS_BBOX_HEIGHT 24

#define VENUS_GROW_SPEED 0.05f

#define VENUS_STATE_IDLE	0
#define VENUS_STATE_GROW_UP	1
#define VENUS_STATE_FIRE	2
#define VENUS_STATE_GROW_DOWN	3



class CVenus : public CGameObject
{
protected:
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


public:
	CVenus(float x, float y);
	virtual void SetState(int state);
};