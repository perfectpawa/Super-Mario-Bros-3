#pragma once
#include "AssetIDs.h"

#define BG_YELLOW 0

class COWMapHolder
{
protected:
	float x;
	float y;
	int width;
	int height;
	int idTextureBG;
public:
	COWMapHolder(float x, float y, int width, int height, int bgColor);
	void Render();
	void DrawBG();
	void DrawBorder();
};