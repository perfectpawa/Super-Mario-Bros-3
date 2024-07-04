#pragma once
#include "GameObject.h"
#include "Animations.h"

#include "Koopas.h"
#include "MarioTail.h"

#include "Portal.h"

#include "debug.h"

#include "AssetIDs.h"

#define MARIO_WALKING_SPEED		0.08f
#define MARIO_GEARING_SPEED		0.12f
#define MARIO_RUNNING_SPEED		0.16f
#define MARIO_MAX_FALL_SPEED		0.3f

#define MARIO_WALK_DECAY 0.0003f
#define MARIO_RUN_DECAY 0.001f

#define MARIO_ACCEL_WALK		0.0005f
#define MARIO_ACCEL_GEAR		0.0005f

#define MARIO_QUICK_JUMP_SPEED_Y	0.25f
#define MARIO_JUMP_SPEED_Y			0.55f
#define MARIO_JUMP_RUN_SPEED_Y		0.65f
#define MARIO_FLY_SPEED_Y		0.4f

#define MARIO_WHIP_RANGE 12.0f

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICK_TIME 100
#define MARIO_WHIP_TIME 400
#define MARIO_FLOAT_TIME 300

#define MARIO_GEAR_UP_TIME 200
#define MARIO_FLYING_TIME 3000

#define MARIO_SWITCH_DELAY_TIME 1000


#define MARIO_GRAVITY			0.002f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f
#define GROUND_Y 160.0f

#pragma region STATE
#define MARIO_STATE_DIE				99
#define MARIO_STATE_IDLE			0

#define MARIO_STATE_WALK_RIGHT			100
#define MARIO_STATE_WALK_LEFT			101
#define MARIO_STATE_GEAR_RIGHT	110
#define MARIO_STATE_GEAR_LEFT	111

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUN_RIGHT			400
#define MARIO_STATE_RUN_LEFT			401

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_HOLD_KOOPAS		700

#define MARIO_STATE_KICK			800
#define MARIO_STATE_WHIP			900
#define MARIO_STATE_FLOAT			901
#define MARIO_STATE_FLY				902

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
	BOOLEAN wantFly;

	BOOLEAN isGearing;
	BOOLEAN isRunning;
	BOOLEAN isMovingRight;
	BOOLEAN isMovingLeft;
	BOOLEAN isFlying;

	float maxVx;
	float maxVy;
	float decayVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	
	int gearUpState;

	int level; 
	int untouchable; 

	ULONGLONG untouchable_start;
	ULONGLONG kick_start;
	ULONGLONG whip_start;
	ULONGLONG float_start;
	ULONGLONG gear_start;
	ULONGLONG flying_start;

	ULONGLONG switch_delay_start;

	BOOLEAN isOnPlatform;
	
	bool wantPickUp = false;
	CKoopas* koopasPickedUp = nullptr;

	CPortal* portalCanUse = nullptr;

	CMarioTail* rightTail = nullptr;
	CMarioTail* leftTail = nullptr;

	int freezeId = -1;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);

	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	void OnCollisionWithSpawnCheck(LPCOLLISIONEVENT e);

	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);

	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);

	void OnCollisionWithCardBlock(LPCOLLISIONEVENT e);



	void TakingDamage();

	void MovingBehavior(DWORD dt);
	void PickUpBehavior();
	void RacoonBehavior();
	void JumpingBehavior();

	void TimeChecking();

	void Landed();


	int GetAniIdSmall();

public:
	CMario(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetState(int& s) { s = this->state; }

	void UpdateOnFreeze(DWORD dt);
	void RenderOnFreeze();

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetLevel(int& l) { l = level; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void GetGearUpState(int& s) { s = gearUpState; }

	void SetWantPickUp(bool b) { wantPickUp = b; }
	void SetWantWhip(bool b) { wantWhip = b; }
	void SetWantJump(bool b) { wantJump = b; }
	void SetWantFly(bool b) { wantFly = b; }
	void SetWantReleaseJump(bool b) { wantReleaseJump = b; }
	void SetWantFloat(bool b) {
		if (isOnPlatform) return;
		wantFloat = b; 
	}

	void SetLookingRight(bool b) { lookingRight = b; }

	void StartGearing() {
		if (!isOnPlatform) return;
		isGearing = true; 
	}

	void EndGearing() { isGearing = false; }

	void SetMovingRight(bool b) { isMovingRight = b; }
	void SetMovingLeft(bool b) { isMovingLeft = b; }

	CPortal* GetPortalCanUse() { return portalCanUse; }

	void StartSwitchingScene();
};
