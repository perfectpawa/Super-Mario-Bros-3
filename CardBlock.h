#pragma once
#include "GameObject.h"

class CCardBlock : public CGameObject
{
public:
	CCardBlock(float x, float y) : CGameObject(x, y) {};

	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};