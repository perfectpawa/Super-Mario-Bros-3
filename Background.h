#pragma once
#include "GameObject.h"

class CBackground : public CGameObject
{
protected:
	int spriteId;
public:
	CBackground(float x, float y, int spriteId) :CGameObject(x, y)
	{
		this->spriteId = spriteId;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();

};