#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define LEAF_GRAVITY 0.0005f
#define LEAF_MAX_FALL_SPEED 0.08f
#define LEAF_STARTUP_BOOST 0.15f
#define LEAF_SWING_ACCELERATION 0.0005f
#define LEAF_SWING_MAX_SPEED 0.13f

#define MAX_Y 200.0f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_STATE_IDLE 10
#define LEAF_STATE_FALL 100

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CLeaf(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};
