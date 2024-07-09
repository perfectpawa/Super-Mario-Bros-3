#pragma once
#include "GameObject.h"
#include "FallCheckingObject.h"
#include "AssetIDs.h"

#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SLIDE_SPEED 0.15f
#define KOOPAS_JUMP_SPEED 0.28f

#define KOOPAS_KNOCK_UP_SPEED 0.3f


#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_HIDE 10

#define KOOPAS_DIE_TIMEOUT 1000
#define KOOPAS_HIDE_TIMEOUT 5000
#define KOOPAS_REVIVE_TIMEOUT 3000

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_HIDE 200
#define KOOPAS_STATE_REVIVE 300
#define KOOPAS_STATE_SLIDE 400
#define KOOPAS_STATE_DIE 500
#define KOOPAS_STATE_KNOCK_DOWN 600
#define KOOPAS_STATE_KNOCK_UP 700


#define KOOPAS_TYPE_ORANGE 1
#define KOOPAS_TYPE_GREEN 2
#define KOOPAS_TYPE_WING 3




class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	int type;

	bool isPickedUp = false;

	bool isUpSideDown = false;

	bool isKnockDown = false;

	ULONGLONG die_start = -1;
	ULONGLONG hide_start;
	ULONGLONG restore_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		if (isKnockDown) return 0;
		return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	void FallChecking(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	

public:
	CGameObject* fallCheckingObject;

	CKoopas(float x, float y, int type);
	virtual void SetState(int state);
	void SetIsPickedUp(bool isPickedUp) { this->isPickedUp = isPickedUp; }
	void GetType(int& type) { type = this->type; }
	void SetType(int type) { this->type = type; }

	virtual void TakeDamage();
	virtual void KnockDown();
	virtual void KnockUp();
};