#pragma once

#include "GameObject.h"

#define TYPE_GREEN 0
#define TYPE_BLACK 1

class CTube : public CGameObject
{
protected:
	int length;				// Unit: cell
	BOOLEAN isUpsideDown;
	int type;
public:
	CTube(float x, float y, int length, BOOLEAN isUpsideDown = false, int type = 0);

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};