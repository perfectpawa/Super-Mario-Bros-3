#include "ColorBox.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"
#include "Mario.h"

void CColorBox::RenderInViewport(int spriteId, float x, float y) {
	CGame* game = CGame::GetInstance();
	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);

	float min_x = cam_x - 16;
	float max_x = cam_x + game->GetBackBufferWidth() + 16;

	if (x >= min_x && x <= max_x)
		CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}


void CColorBox::Render()
{
	float cellHeight_div_2 = this->cellHeight / 2;
	float cellWidth_div_2 = this->cellWidth / 2;
	float xx = x - cellWidth_div_2;
	float yy = y - cellHeight_div_2;

	// Top
	RenderInViewport(this->spriteIdTopLeft, xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->width - 1; i++)
	{
		RenderInViewport(this->spriteIdTopMiddle, xx, yy);
		xx += this->cellWidth;
	}
	if (width > 1)
		RenderInViewport(this->spriteIdTopRight, xx, yy);

	// Middle have height - 2 rows
	for (int i = 1; i < this->height - 1; i++)
	{
		xx = x - cellWidth_div_2;
		yy += this->cellHeight;
		RenderInViewport(this->spriteIdMiddleLeft, xx, yy);
		xx += this->cellWidth;
		for (int j = 1; j < this->width - 1; j++)
		{
			RenderInViewport(this->spriteIdMiddleMiddle, xx, yy);
			xx += this->cellWidth;
		}
		if (width > 1)
			RenderInViewport(this->spriteIdMiddleRight, xx, yy);
	}

	// Bottom
	xx = x - cellWidth_div_2;
	yy += this->cellHeight;
	RenderInViewport(this->spriteIdBottomLeft, xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->width - 1; i++)
	{
		RenderInViewport(this->spriteIdBottomMiddle, xx, yy);
		xx += this->cellWidth;
	}
	if (width > 1)
		RenderInViewport(this->spriteIdBottomRight, xx, yy);

	//RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth;
	t = y - this->cellWidth;
	r = l + this->cellWidth * this->width;
	b = t + this->cellHeight * this->height;
}

void CColorBox::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth + rect.right / 2;
	float yy = y - this->cellHeight + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}