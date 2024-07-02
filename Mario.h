#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Koopas.h"

#include "debug.h"

#include "AssetIDs.h"

#define MARIO_WALKING_SPEED		0.1f	// 5 block 1s
#define MARIO_WALKING_FAST_SPEED		0.18f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_MAX_FALL_SPEED		0.5f

#define MARIO_SPRINT_SPEED_STATE_1		0.10f
#define MARIO_SPRINT_SPEED_STATE_2		0.12f
#define MARIO_SPRINT_SPEED_STATE_3		0.14f
#define MARIO_SPRINT_SPEED_STATE_4		0.16f

#define MARIO_WALK_DECAY 0.0003f
#define MARIO_WALK_FAST_DECAY 0.0005f
#define MARIO_RUN_DECAY 0.001f

#define MARIO_ACCEL_WALK_X	0.001f
#define MARIO_ACCEL_WALK_FAST_X	0.0001f
#define MARIO_ACCEL_RUN_X	0.004f

#define MARIO_QUICK_JUMP_SPEED_Y	0.25f
#define MARIO_JUMP_SPEED_Y			0.5f
#define MARIO_JUMP_RUN_SPEED_Y		0.65f
#define MARIO_FLY_SPEED_Y		1.0f

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 100
#define MARIO_WHIP_TIME 200
#define MARIO_SPRINT_TIME 700
#define MARIO_FLOAT_TIME 300

#define MARIO_GRAVITY			0.002f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f
#define GROUND_Y 160.0f

#pragma region STATE
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
#define MARIO_STATE_FLOATING			901
#define MARIO_STATE_FLYING			902

#pragma endregion


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

#define MARIO_RACOON_BBOX_WIDTH  18



class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN lookingRight;

	BOOLEAN wantWhip;
	BOOLEAN wantJump;
	BOOLEAN wantReleaseJump;
	BOOLEAN wantFloat;

	BOOLEAN isSprinting;
	BOOLEAN isRunning;
	BOOLEAN isMovingRight;
	BOOLEAN isMovingLeft;

	float maxVx;
	float maxVy;
	float decayVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	
	int powerSprintState;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG whip_start;
	ULONGLONG sprint_start;
	ULONGLONG float_start;

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
	void OnCollisionWithButton(LPCOLLISIONEVENT e);


	void TakingDamage();

	void MovingBehavior(DWORD dt);
	void PickUpBehavior();
	void RacoonBehavior();
	void JumpingBehavior();

	void TimeChecking();

	void Landed();


	int GetAniIdSmall();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		lookingRight = true;

		wantWhip = false;
		wantJump = false;
		wantReleaseJump = false;
		wantFloat = false;

		isSprinting = false;
		isRunning = false;
		isMovingRight = false;
		isMovingLeft = false;

		maxVx = 0.0f;
		maxVy = MARIO_MAX_FALL_SPEED;
		decayVx = MARIO_WALK_DECAY;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;

		untouchable_start = -1;
		kick_start = -1;
		whip_start = -1;
		sprint_start = -1;
		float_start = -1;

		isOnPlatform = false;
		coin = 0;
		powerSprintState = 0;
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

	void GetPowerSprintState(int& s) { s = powerSprintState; }

	void GetCoin(int& c) { c = coin; }
	
	void SetWantPickUp(bool b) { wantPickUp = b; }
	void SetWantWhip(bool b) { wantWhip = b; }
	void SetWantJump(bool b) { wantJump = b; }
	void SetWantReleaseJump(bool b) { wantReleaseJump = b; }
	void SetWantFloat(bool b) {
		if (isOnPlatform) return;
		wantFloat = b; 
	}

	void SetLookingRight(bool b) { lookingRight = b; }

	void StartSprinting() {
		if (!isOnPlatform) return;
		isSprinting = true; 
		sprint_start = GetTickCount64(); 
	}
	void ResetSprint() { sprint_start = GetTickCount64(); isRunning = false; }
	void StopSprinting() { isSprinting = false; sprint_start = -1; isRunning = false; }

	void SetRunning(bool b) { isRunning = b; }
	void SetMovingRight(bool b) { isMovingRight = b; }
	void SetMovingLeft(bool b) { isMovingLeft = b; }

};