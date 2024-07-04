#include "Portal.h"
#include "Game.h"
#include "Textures.h"
#include "AssetIDs.h"
#include "debug.h"

CPortal::CPortal(float x, float y, float width, float height, 
				bool isMainPortal, int scene_id, int keyCode, 
				int dir_x, int dir_y,
				bool haveStartPos, float start_x, float start_y
) : CGameObject(x, y)
{
	this->width = width;
	this->height = height;

	this->isMainPortal = isMainPortal;
	this->scene_id = scene_id;
	this->keyCode = keyCode;

	this->haveStartPos = haveStartPos;
	this->start_x = start_x;
	this->start_y = start_y;

	this->dir_x = dir_x;
	this->dir_y = dir_y;

	if (isMainPortal) {
		CPortal* leftPseudoPortal = new CPortal(x - width * 2.5f, y, width / 2, height * 2, false);
		CPortal* rightPseudoPortal = new CPortal(x + width * 2.5f, y, width / 2, height * 2, false);
		CPortal* topPseudoPortal = new CPortal(x, y - height * 2.5f, width * 2, height / 2, false);
		CPortal* bottomPseudoPortal = new CPortal(x, y + height * 2.5f, width * 2, height / 2, false);

		CGame::GetInstance()->GetCurrentScene()->AddObject(leftPseudoPortal, OBJECT_TYPE_PORTAL);
		CGame::GetInstance()->GetCurrentScene()->AddObject(rightPseudoPortal, OBJECT_TYPE_PORTAL);
		CGame::GetInstance()->GetCurrentScene()->AddObject(topPseudoPortal, OBJECT_TYPE_PORTAL);
		CGame::GetInstance()->GetCurrentScene()->AddObject(bottomPseudoPortal, OBJECT_TYPE_PORTAL);
	}

}

void CPortal::RenderBoundingBox()
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

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = x + width/2;
	b = y + height/2;
}

void CPortal::SwitchScene()
{
	CGame::GetInstance()->InitiateSwitchScene(scene_id);
	if(haveStartPos)
		CGame::GetInstance()->InitDefaulePos(start_x, start_y);
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);
}