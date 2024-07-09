#include "MarioTail.h"

#include "Goomba.h"
#include "ParaGoomba.h"
#include "Koopas.h"
#include "Plant.h"
#include "Brick.h"
#include "BrickCoin.h"
#include "CollisionEffect.h"
#include "QuestionBlock.h"

#include "debug.h"
#include "PlayScene.h"

CMarioTail::CMarioTail()
{
}

void CMarioTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMarioTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0) return;

	if(dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

		if (goomba->GetState() == GOOMBA_STATE_WALKING) {
			goomba->TakeDamage(true);
			float x, y;
			goomba->GetPosition(x, y);
			CEffectObject* effect = new CCollisionEffect(x, y);
			dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddEffect(effect);
		}
	}
	else if(dynamic_cast<CParaGoomba*>(e->obj))
	{
		CParaGoomba* goomba = dynamic_cast<CParaGoomba*>(e->obj);

		if (goomba->GetState() != GOOMBA_STATE_DIE &&
			goomba->GetState() != GOOMBA_STATE_KNOCKOUT
			) {
			goomba->TakeDamage(true);
			float x, y;
			goomba->GetPosition(x, y);
			CEffectObject* effect = new CCollisionEffect(x, y);
			dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddEffect(effect);
		}
	}
	if(dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		koopas->KnockUp();
		float x, y;
		koopas->GetPosition(x, y);
		CEffectObject* effect = new CCollisionEffect(x, y);
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddEffect(effect);
	}

	if(dynamic_cast<CBrickCoin*>(e->obj))
	{
		CBrickCoin* brick = dynamic_cast<CBrickCoin*>(e->obj);
		brick->Breaking(true);
	}
	else
	if(dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		brick->Breaking();
	}

	if(dynamic_cast<CQuestionBlock*>(e->obj))
	{
		CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);
		if (questionBlock->GetState() == QBLOCK_STATE_IDLE) {
			questionBlock->SetState(QBLOCK_STATE_BOUND_UP);
		}
	}

	if(dynamic_cast<CPlant*>(e->obj))
	{
		CPlant* plant = dynamic_cast<CPlant*>(e->obj);
		plant->TakeDamage();
	}

}

void CMarioTail::Update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void CMarioTail::Render()
{
	//RenderBoundingBox();
}

void CMarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_TAIL_BBOX_WIDTH / 2;
	top = y - MARIO_TAIL_BBOX_HEIGHT / 2;
	right = left + MARIO_TAIL_BBOX_WIDTH;
	bottom = top + MARIO_TAIL_BBOX_HEIGHT;
}