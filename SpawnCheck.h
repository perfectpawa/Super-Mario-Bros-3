#pragma once
#include "GameObject.h"

#define SPAWN_CHECK_BBOX_WIDTH 20
#define SPAWN_CHECK_BBOX_HEIGHT 220
class CSpawnCheck : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
};