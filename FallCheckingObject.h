#pragma once
#include "GameObject.h"

#define GRAVITY 0.005f
#define WALKING_SPEED 0.05f
#define BBOX_WIDTH 15
#define BBOX_HEIGHT 24

class CFallCheckingObject : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFallCheckingObject(float x, float y);
};