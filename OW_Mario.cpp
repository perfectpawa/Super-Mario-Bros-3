#include "OW_Mario.h"
#include "debug.h"

COWMario::COWMario(float x, float y, bool canGoIn) : COWGameObject(x, y, canGoIn)
{
	DebugOut(L"[INFO] OW_Mario created!\n");
}

void COWMario::Update(DWORD dt, vector<COWGameObject*>* coObjects)
{

}

void COWMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_OW_MARIO_SMALL;

	animations->Get(aniId)->Render(x, y);
}