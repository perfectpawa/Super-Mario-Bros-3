#pragma once
#include "EffectObject.h"

#define TIME_COLLISION_EFFECT 200

class CCollisionEffect : public CEffectObject {
protected:
	ULONGLONG time_start;
public:
	CCollisionEffect(float x, float y);
	virtual void Update(DWORD dt);
	void Render();
};