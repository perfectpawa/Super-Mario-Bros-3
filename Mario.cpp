#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "ParaGoomba.h"
#include "Koopas.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Portal.h"
#include "SpawnCheck.h"
#include "QuestionBlock.h"
#include "Venus.h"
#include "FireShot.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (koopasPickedUp != NULL && !wantPickUp) {
		koopasPickedUp->SetState(KOOPAS_STATE_SLIDE);
		float koopas_x, koopas_y;
		koopasPickedUp->GetPosition(koopas_x, koopas_y);
		if (koopas_x < x)
			koopasPickedUp->SetSpeed(-KOOPAS_SLIDE_SPEED, 0);
		else
			koopasPickedUp->SetSpeed(KOOPAS_SLIDE_SPEED, 0);

		koopasPickedUp->SetIsPickedUp(false);
		koopasPickedUp = NULL;
	}

	if (koopasPickedUp != NULL) {
		if (koopasPickedUp->GetState() == KOOPAS_STATE_WALKING) {
			koopasPickedUp->SetIsPickedUp(false);
			koopasPickedUp = NULL;
		}
		else {
			int offset = 12;
			if (nx < 0)
				offset *= -1;
			if (x != 0) {
				koopasPickedUp->SetPosition(x + offset, y);
			}
		}
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CSpawnCheck*>(e->obj))
		OnCollisionWithSpawnCheck(e);
	else if (dynamic_cast<CMushroom*>(e->obj)) 
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CVenus*>(e->obj))
		OnCollisionWithVenus(e);
	else if (dynamic_cast<CFireShot*>(e->obj))
		OnCollisionWithFireShot(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);


	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == GOOMBA_STATE_DIE) return;
		//check is para goomba
		if (dynamic_cast<CParaGoomba*>(goomba))
		{
			CParaGoomba* paraGoomba = dynamic_cast<CParaGoomba*>(goomba);
			if (paraGoomba->IsHaveWing())
				paraGoomba->BreakWing();
			else if (goomba->GetState() != GOOMBA_STATE_DIE)
				goomba->SetState(GOOMBA_STATE_DIE);
		}
		else if (goomba->GetState() != GOOMBA_STATE_DIE)
			goomba->SetState(GOOMBA_STATE_DIE);

		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else // hit by Goomba
	{
		if(goomba->GetState() != GOOMBA_STATE_DIE)
			TakingDamage();
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	int type;
	koopas->GetType(type);

	if (koopas == koopasPickedUp) return;

	if (koopas->GetState() == KOOPAS_STATE_HIDE || koopas->GetState() == KOOPAS_STATE_REVIVE) {

		if (wantPickUp) {
			koopasPickedUp = koopas;
			koopasPickedUp->SetIsPickedUp(true);
			return;
		}

		koopas->SetState(KOOPAS_STATE_SLIDE);

		float koopas_x, koopas_y;
		koopas->GetPosition(koopas_x, koopas_y);
		if (koopas_x < x)
			koopas->SetSpeed(-KOOPAS_SLIDE_SPEED, 0);
		else
			koopas->SetSpeed(KOOPAS_SLIDE_SPEED, 0);

	}
	else {
		if (e->ny < 0) {
			if (type == KOOPAS_TYPE_WING) {
				koopas->SetType(KOOPAS_TYPE_GREEN);
			}
			else if (koopas->GetState() == KOOPAS_STATE_WALKING)
			{
				koopas->SetState(KOOPAS_STATE_HIDE);
			}
			else if (koopas->GetState() == KOOPAS_STATE_SLIDE)
			{
				koopas->SetState(KOOPAS_STATE_HIDE);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else {
			if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_SLIDE)
			{
				TakingDamage();
			}
		}
	}
}	

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario:: OnCollisionWithSpawnCheck(LPCOLLISIONEVENT e)
{
	//delete spawn check
	e->obj->Delete();
	DebugOut(L"---Collision with spawn check---- \n");

}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (level == MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_BIG;
		y -= (float)(MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}

	mushroom->Delete();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e) {
	if (e->ny <= 0) return;

	CQuestionBlock* questionBlock = dynamic_cast<CQuestionBlock*>(e->obj);
	if (questionBlock->GetState() == QBLOCK_STATE_IDLE) {
		questionBlock->SetState(QBLOCK_STATE_BOUND_UP);
		if (questionBlock->GetRewardType() == REWARD_COIN)
			coin++;
	}
}

void CMario::OnCollisionWithVenus(LPCOLLISIONEVENT e)
{
	CVenus* venus = dynamic_cast<CVenus*>(e->obj);
	TakingDamage();
}

void CMario::OnCollisionWithFireShot(LPCOLLISIONEVENT e)
{
	CFireShot* fireShot = dynamic_cast<CFireShot*>(e->obj);
	TakingDamage();
	fireShot->Delete();
}

void CMario::TakingDamage() {
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (koopasPickedUp != NULL)
	{
		if (!isOnPlatform) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_PICK_UP_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_PICK_UP_JUMP_LEFT;
		}
		else {
			if (vx == 0) {
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_PICK_UP_IDLE_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_PICK_UP_IDLE_LEFT;
			}
			else {
				if (nx > 0)
					aniId = ID_ANI_MARIO_SMALL_PICK_UP_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_PICK_UP_LEFT;
			}
		}

	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (koopasPickedUp != NULL) {
		if (!isOnPlatform) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_PICK_UP_JUMP_RIGHT;
			else
				aniId = ID_ANI_MARIO_PICK_UP_JUMP_LEFT;
		}
		else {
			if (vx == 0) {
				if (nx > 0)
					aniId = ID_ANI_MARIO_PICK_UP_IDLE_RIGHT;
				else
					aniId = ID_ANI_MARIO_PICK_UP_IDLE_LEFT;
			}
			else {
				if (nx > 0)
					aniId = ID_ANI_MARIO_PICK_UP_RIGHT;
				else
					aniId = ID_ANI_MARIO_PICK_UP_LEFT;
			}
		}

	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (state == MARIO_STATE_HOLD_KOOPAS)
		aniId = ID_ANI_MARIO_SIT_LEFT;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (float)(MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

