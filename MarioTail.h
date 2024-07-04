#pragma once
#include "GameObject.h"

#define MARIO_TAIL_BBOX_WIDTH 8
#define MARIO_TAIL_BBOX_HEIGHT 8

class CMarioTail : public CGameObject
{
public:
	CMarioTail();
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
};