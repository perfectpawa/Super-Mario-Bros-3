#include "CollisionEffect.h"

CCollisionEffect::CCollisionEffect(float x, float y) : CEffectObject(x, y)
{
	time_start = GetTickCount64();
}

void CCollisionEffect::Update(DWORD dt)
{
	if (GetTickCount64() - time_start > TIME_COLLISION_EFFECT)
	{
		this->Delete();
	}
}

void CCollisionEffect::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_EFFECT_TAKE_DOWN)->Render(x, y);
}