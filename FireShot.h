#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define FIRE_BBOX_WIDTH 9
#define FIRE_BBOX_HEIGHT 9

#define FIRE_SPEED 0.05f




class CFireShot : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


public:
	CFireShot(float x, float y, float vx, float vy);
};