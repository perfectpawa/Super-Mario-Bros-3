#include "Koopas.h"
#include "Goomba.h"
#include "FallCheckingObject.h"
#include "QuestionBlock.h"
#include "Brick.h"
#include "ScoreEffect.h"
#include "CollisionEffect.h"
#include "PlayScene.h"

CKoopas::CKoopas(float x, float y, int type) :CGameObject(x, y)
{
	this->type = type;

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
	if (isPickedUp) return;

	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);

	if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);

	if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);

	if(dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);


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
	if (state == KOOPAS_STATE_HIDE || state == KOOPAS_STATE_REVIVE) {

		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		float vx, vy;
		goomba->GetSpeed(vx, vy);
		goomba->SetSpeed(-vx, vy);

		return;
	}

	if (state != KOOPAS_STATE_SLIDE) return;
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->TakeDamage(true);
		float x, y;
		goomba->GetPosition(x, y);
		CEffectObject* effect = new CCollisionEffect(x, y);
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->AddEffect(effect);
	}
}

void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	
	if (koopas->GetState() == KOOPAS_STATE_HIDE && this->state == KOOPAS_STATE_WALKING) {
		vx = -vx;
	}

	if (state != KOOPAS_STATE_SLIDE) return;

	if (koopas->GetState() != KOOPAS_STATE_SLIDE)
	{
		koopas->KnockDown();
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

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (state != KOOPAS_STATE_SLIDE) return;
	if (e->ny != 0) return;
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	brick->Breaking();

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (die_start != -1 && GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT)
	{
		this->Delete();
	}

	if (isKnockDown) {
		vy += ay * dt;
		x += vx * dt;
		y += vy * dt;
		return;
	}

	if (type == KOOPAS_TYPE_WING) {
		if(vy == 0)
			vy = -KOOPAS_JUMP_SPEED;
	}
	else {
		FallChecking(dt, coObjects);
	}

	if (isPickedUp) {
		ay = 0;
	}

	if ((state == KOOPAS_STATE_HIDE) && (GetTickCount64() - hide_start > KOOPAS_HIDE_TIMEOUT))
	{
		SetState(KOOPAS_STATE_REVIVE);
	}
	if ((state == KOOPAS_STATE_REVIVE) && (GetTickCount64() - restore_start > KOOPAS_REVIVE_TIMEOUT)) {
		SetState(KOOPAS_STATE_WALKING);
	}

	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::FallChecking(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	float fallCheckingObject_vx, fallCheckingObject_vy;
	fallCheckingObject->GetSpeed(fallCheckingObject_vx, fallCheckingObject_vy);
	if (fallCheckingObject_vy != 0 && vy == 0 && state == KOOPAS_STATE_WALKING)
	{
		vx = -vx;
		if (vx > 0)
			fallCheckingObject->SetPosition(x + 16, y);
		else
			fallCheckingObject->SetPosition(x - 16, y);

		if (vx * fallCheckingObject_vx < 0)
			fallCheckingObject->SetSpeed(-fallCheckingObject_vx, fallCheckingObject_vy);

	}

	fallCheckingObject->Update(dt, coObjects);
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

	if (type == KOOPAS_TYPE_GREEN) {
		aniId += 10000;
	}

	if(type == KOOPAS_TYPE_WING)
	{
		aniId = ID_ANI_WING_GREEN_KOOPAS_WALKING;
		if(vx > 0)
			aniId = ID_ANI_WING_GREEN_KOOPAS_FLIP_WALKING;
	}

	float rotate = 0;
	if(isUpSideDown)
	{
		rotate = 180;
		rotate = rotate * 3.14f / 180;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, rotate);
	//RenderBoundingBox();

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

		isUpSideDown = false;

		fallCheckingObject->SetPosition(x - 16, y);
		
		float fallCheckingObject_vx, fallCheckingObject_vy;
		fallCheckingObject->GetSpeed(fallCheckingObject_vx, fallCheckingObject_vy);
		
		if(vx * fallCheckingObject_vx < 0)
			fallCheckingObject->SetSpeed(-fallCheckingObject_vx, fallCheckingObject_vy);

		break;
	}
}

void CKoopas::TakeDamage()
{
	if (type == KOOPAS_TYPE_WING) {
		this->SetType(KOOPAS_TYPE_GREEN);
	}
	else if (this->GetState() == KOOPAS_STATE_WALKING)
	{
		this->SetState(KOOPAS_STATE_HIDE);
	}
	else if (this->GetState() == KOOPAS_STATE_SLIDE)
	{
		this->SetState(KOOPAS_STATE_HIDE);
	}
}

void CKoopas::KnockUp() {
	if (type == KOOPAS_TYPE_WING) {
		this->SetType(KOOPAS_TYPE_GREEN);
		return;
	}

	this->SetState(KOOPAS_STATE_HIDE);
	isUpSideDown = true;
	vy -= KOOPAS_KNOCK_UP_SPEED;
}

void CKoopas::KnockDown() {
	isKnockDown = true;
	isUpSideDown = true;

	if (type == KOOPAS_TYPE_WING) this->SetType(KOOPAS_TYPE_GREEN);

	SetState(KOOPAS_STATE_HIDE);

	vy -= KOOPAS_KNOCK_UP_SPEED / 2;
	die_start = GetTickCount64();

	CEffectObject* effect = new CScoreEffect(x, y, 100);
	CPlayScene * scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	scene->AddEffect(effect);

	effect = new CCollisionEffect(x, y);
	scene->AddEffect(effect);
}
