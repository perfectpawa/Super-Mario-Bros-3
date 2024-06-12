#pragma once
#include "GameObject.h"

class CColorBox : public CGameObject
{
protected:
	float cellWidth;
	float cellHeight;
	int width;
	int height;
	int spriteIdTopLeft, spriteIdTopMiddle, spriteIdTopRight;
	int spriteIdMiddleLeft, spriteIdMiddleMiddle, spriteIdMiddleRight;
	int spriteIdBottomLeft, spriteIdBottomMiddle, spriteIdBottomRight;

public:
	CColorBox(float x, float y,
		float cell_width, float cell_height,
		int width, int height,
		int color_id
		) :CGameObject(x, y)
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;

		this->width = width;
		this->height = height;
		this->spriteIdTopLeft = color_id + 1;
		this->spriteIdTopMiddle = color_id + 2;
		this->spriteIdTopRight = color_id + 3;
		this->spriteIdMiddleLeft = color_id + 4;
		this->spriteIdMiddleMiddle = color_id + 5;
		this->spriteIdMiddleRight = color_id + 6;
		this->spriteIdBottomLeft = color_id + 7;
		this->spriteIdBottomMiddle = color_id + 8;
		this->spriteIdBottomRight = color_id + 9;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsDirectionColliable(float nx, float ny) {
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
	
};

typedef CColorBox* LPCOLORBOX;