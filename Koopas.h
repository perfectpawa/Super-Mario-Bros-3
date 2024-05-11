#pragma once
#include "GameObject.h"
#include "FallCheckingObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_SLIDE_SPEED 0.1f


#define KOOPAS_BBOX_WIDTH 15
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_HIDE 10

#define KOOPAS_DIE_TIMEOUT 500
#define KOOPAS_HIDE_TIMEOUT 4000
#define KOOPAS_RESTORE_TIMEOUT 1000

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_HIDE 200
#define KOOPAS_STATE_RESTORE 300
#define KOOPAS_STATE_SLIDE 400
#define KOOPAS_STATE_DIE 500

#define ID_ANI_KOOPAS_WALKING 6000
#define ID_ANI_KOOPAS_HIDE 6001
#define ID_ANI_KOOPAS_RESTORE 6002
#define ID_ANI_KOOPAS_HIDE_SLIDE 6003
#define ID_ANI_KOOPAS_DIE 6004

#define ID_ANI_KOOPAS_FLIP_WALKING 6010

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG hide_start;
	ULONGLONG restore_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
	CGameObject* fallCheckingObject;
};