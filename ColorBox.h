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
		int sprite_id_top_left, int sprite_id_top_middle, int sprite_id_top_right,
		int sprite_id_middle_left, int sprite_id_middle_middle, int sprite_id_middle_right,
		int sprite_id_bottom_left, int sprite_id_bottom_middle, int sprite_id_bottom_right
		) :CGameObject(x, y)
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;

		this->width = width;
		this->height = height;

		this->spriteIdTopLeft = sprite_id_top_left;
		this->spriteIdTopMiddle = sprite_id_top_middle;
		this->spriteIdTopRight = sprite_id_top_right;

		this->spriteIdMiddleLeft = sprite_id_middle_left;
		this->spriteIdMiddleMiddle = sprite_id_middle_middle;
		this->spriteIdMiddleRight = sprite_id_middle_right;

		this->spriteIdBottomLeft = sprite_id_bottom_left;
		this->spriteIdBottomMiddle = sprite_id_bottom_middle;
		this->spriteIdBottomRight = sprite_id_bottom_right;
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