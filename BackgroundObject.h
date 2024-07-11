#pragma once
#include "Mario.h"

#define TYPE_CLOUD		0
#define TYPE_GRASS		1
#define TYPE_BUSH_SMALL	2
#define TYPE_BUSH_BIG_1	3
#define TYPE_BUSH_BIG_2	4
#define TYPE_BUSH_TALL	5
#define TYPE_BLACK_BACKGROUND	10
#define TYPE_BLACK_BACKGROUND_BOUNDARY	11
#define TYPE_BLACK_BUSH_SMALL	12
#define TYPE_BLACK_BUSH_MEDIUM	13

class CBackgroundObject
{
protected:
	float x;
	float y;
	int type;
	int length;
public:
	CBackgroundObject(float x, float y, int type, int length = 1);
	void Render();
	void RenderInViewport(int spriteId, float x, float y);
	void RenderCloud();
	void RenderGrass();
	void RenderBushSmall();
	void RenderBushBig1();
	void RenderBushBig2();
	void RenderBushTall();
	void RenderBlackBackground();
	void RenderBlackBackgroundBoundary();
	void RenderBlackBushSmall();
	void RenderBlackBushMedium();
};