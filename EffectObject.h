#pragma once
#include "Collision.h"
#include "Animations.h"
#include "Sprites.h"
#include "AssetIDs.h"

class CEffectObject {
protected:
	float x;
	float y;
	bool isDeleted = false;
public:
	CEffectObject(float x, float y) : x(x), y(y) {}
	virtual void Render() = 0;
	virtual void Update(DWORD dt) = 0;
	void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
};