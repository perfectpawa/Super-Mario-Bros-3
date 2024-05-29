#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define VENUS_BBOX_WIDTH 15
#define VENUS_BBOX_HEIGHT 40

#define VENUS_GROW_SPEED 0.05f
#define VENUS_ATK_RANGE 160
#define VENUS_IDLE_TIME 2000
#define VENUS_AIM_TIME 1000
#define VENUS_FIRE_TIME 1000

#define VENUS_STATE_IDLE	10
#define VENUS_STATE_GROW_UP	20
#define VENUS_STATE_AIM	30
#define VENUS_STATE_FIRE	40
#define VENUS_STATE_GROW_DOWN	50



class CVenus : public CGameObject
{
protected:
	float mx = 0;
	float my = -1;

	ULONGLONG idleTime;
	ULONGLONG aimTime;
	ULONGLONG fireTime;

	float idlePosY = 0;
	float firePosY = 0;

	LPGAMEOBJECT player = NULL;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);


public:
	CVenus(float x, float y);
	virtual void SetState(int state);
};