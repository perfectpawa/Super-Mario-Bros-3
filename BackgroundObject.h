#pragma once

#define TYPE_CLOUD		0
#define TYPE_GRASS		1
#define TYPE_BUSH_SMALL	2
#define TYPE_BUSH_BIG_1	3
#define TYPE_BUSH_BIG_2	4

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
	void RenderCloud();
	void RenderGrass();
	void RenderBushBig1();
};