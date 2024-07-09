#include "Button.h"
#include "debug.h"
#include "PlayScene.h"
CButton::CButton(float x, float y) : CGameObject(x, y)
{
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 12 / 2;
	t = y - 16 / 2;
	r = l + 12;
	b = t + 16;
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (pressed && GetTickCount64() - countdown_start > COUNTDOWN)
	{
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->ChangeBrickCoin(1);
		countdown_start = -1;
	}
}

void CButton::Render()
{
	if (pressed) CSprites::GetInstance()->Get(ID_SPRITE_BUTTON_PRESSED)->Draw(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_BUTTON)->Render(x, y);
}

void CButton::Pressing()
{
	if(pressed) return;
	pressed = true;
	countdown_start = GetTickCount64();
	CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	scene->ChangeBrickCoin(0);
	scene->CamSkake();
}