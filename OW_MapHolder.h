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
public:
	COWMapHolder(float x, float y, int width, int height);
	void Render();
	void DrawBorder();
};