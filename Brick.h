#pragma once

#include "GameObject.h"
#include "AssetIDs.h"

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define TYPE_BREAKABLE 0
#define TYPE_UNBREAKABLE 1

class CBrick : public CGameObject {
protected:
	int type;
	int spriteId;
public:
	CBrick(float x, float y, int type, int spriteId = -1);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};