#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Koopas.h"

#include "debug.h"

#include "AssetIDs.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_WALKING_FAST_SPEED		0.15f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_WALK_FAST_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.001f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				99
#define MARIO_STATE_IDLE			0

#define MARIO_STATE_WALKING_RIGHT			100
#define MARIO_STATE_WALKING_LEFT			101
#define MARIO_STATE_WALKING_FAST_RIGHT	110
#define MARIO_STATE_WALKING_FAST_LEFT	111

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT			400
#define MARIO_STATE_RUNNING_LEFT			401

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLD_KOOPAS		700

#define MARIO_STATE_KICK			800
#define MARIO_STATE_WHIP			900

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON		3

#define MARIO_BIG_BBOX_WIDTH  12
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  8
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

#define MARIO_KICK_TIME 100
#define MARIO_WHIP_TIME 500
#define MARIO_SPRINT_TIME 500


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN lookingRight;

	BOOLEAN wantWhip;
	BOOLEAN isSprinting;
	BOOLEAN isRunning;
	BOOLEAN isMovingRight;
	BOOLEAN isMovingLeft;


	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG whip_start;
	ULONGLONG sprint_start;

	BOOLEAN isOnPlatform;
	int coin;
	
	bool wantPickUp = false;
	CKoopas* koopasPickedUp = NULL;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithVenus(LPCOLLISIONEVENT e);


	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	void OnCollisionWithSpawnCheck(LPCOLLISIONEVENT e);

	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithFireShot(LPCOLLISIONEVENT e);

	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);

	void TakingDamage();

	int GetAniIdSmall();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		lookingRight = true;

		wantWhip = false;
		isSprinting = false;
		isRunning = false;
		isMovingRight = false;
		isMovingLeft = false;

		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;

		untouchable_start = -1;
		kick_start = -1;
		whip_start = -1;
		sprint_start = -1;

		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetState(int& s) { s = this->state; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	//int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetLevel(int& l) { l = level; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetWantPickUp(bool b) { wantPickUp = b; }
	
	void SetLookingRight(bool b) { lookingRight = b; }
	void SetCanWhip(bool b) { wantWhip = b; }

	void StartSprinting() { isSprinting = true; sprint_start = GetTickCount64(); }
	void StopSprinting() { isSprinting = false; sprint_start = -1; isRunning = false; }
	
	void SetRunning(bool b) { isRunning = b; }
	void SetMovingRight(bool b) { isMovingRight = b; }
	void SetMovingLeft(bool b) { isMovingLeft = b; }
};