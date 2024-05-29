#include "Koopas.h"
#include "Goomba.h"
#include "FallCheckingObject.h"
#include "QuestionBlock.h"


CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	hide_start = -1;
	restore_start = -1;
	fallCheckingObject = new CFallCheckingObject(x - 16, y);
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_WALKING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_HIDE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_HIDE;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);

	if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);

	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CFallCheckingObject*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_SLIDE) return;
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}

void CKoopas::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_SLIDE) return;
	if(e->ny != 0) return;
	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);

	if (questionBlock->GetState() == QBLOCK_STATE_IDLE)
	{
		questionBlock->SetState(QBLOCK_STATE_BOUND_UP);
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	float fallCheckingObject_xy, fallCheckingObject_vy;
	fallCheckingObject->GetSpeed(fallCheckingObject_xy, fallCheckingObject_vy);
	if (fallCheckingObject_vy != 0 && vy == 0 && state == KOOPAS_STATE_WALKING)
	{
		vx = -vx;
		if(vx > 0)
			fallCheckingObject->SetPosition(x + 16, y);
		else
			fallCheckingObject->SetPosition(x - 16, y);

		fallCheckingObject->SetSpeed(-fallCheckingObject_xy, fallCheckingObject_vy);
	}

	if (isPickedUp) {
		ay = 0;
	}

	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPAS_STATE_HIDE) && (GetTickCount64() - hide_start > KOOPAS_HIDE_TIMEOUT))
	{
		SetState(KOOPAS_STATE_REVIVE);
	}
	if ((state == KOOPAS_STATE_REVIVE) && (GetTickCount64() - restore_start > KOOPAS_REVIVE_TIMEOUT)) {
		SetState(KOOPAS_STATE_WALKING);
	}


	fallCheckingObject->Update(dt, coObjects);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;
	if (vx > 0)
	{
		aniId = ID_ANI_KOOPAS_FLIP_WALKING;
	}
	if (state == KOOPAS_STATE_HIDE)
	{
		aniId = ID_ANI_KOOPAS_HIDE;
	}
	if (state == KOOPAS_STATE_REVIVE) {
		aniId = ID_ANI_KOOPAS_REVIVE;
	}
	if (state == KOOPAS_STATE_SLIDE) {
		aniId = ID_ANI_KOOPAS_SLIDE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	fallCheckingObject->Render();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		break;
	case KOOPAS_STATE_HIDE:
		hide_start = GetTickCount64();
		y -= KOOPAS_BBOX_HEIGHT_HIDE / 2;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_REVIVE:
		restore_start = GetTickCount64();
		break;
	case KOOPAS_STATE_SLIDE:
		y -= KOOPAS_BBOX_HEIGHT_HIDE / 2;
		vx = KOOPAS_SLIDE_SPEED;
		ay = KOOPAS_GRAVITY;
		die_start = -1;
		hide_start = -1;
		restore_start = -1;
		break;
	case KOOPAS_STATE_WALKING:
		y -= (float)(KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_HIDE) / 2;

		vx = -KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		die_start = -1;
		hide_start = -1;
		restore_start = -1;

		fallCheckingObject->SetPosition(x - 16, y);

		break;
	}
}
