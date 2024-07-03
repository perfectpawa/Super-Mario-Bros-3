#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PLANT_COLOR_RED 1
#define PLANT_COLOR_GREEN 2

#define PLANT_BBOX_WIDTH 16
#define PLANT_PART_BBOX_HEIGHT 8

#define PLANT_STATE_IDLE 0
#define PLANT_STATE_GROW_UP 1
#define PLANT_STATE_ATTACK 2
#define PLANT_STATE_GROW_DOWN 3

#define PLANT_GROW_SPEED	0.05f

#define PLANT_ATTACK_RANGE 112
#define PLANT_HIDE_RANGE 18

#define PLANT_GROW_UP_DELAY 2000 
#define PLANT_ATTACK_TIME 1000

class CPlant : public CGameObject
{
protected:
	int height;
	int color;
	int state;

	int plant_height;

	float up_point;
	float down_point;

	bool playerInLeft = true;


	ULONGLONG delay_start = -1;
	ULONGLONG attack_start = -1;

	CMario* player;
public:
	CPlant(float x, float y, int height = 2, int color = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual void SetState(int state);
	virtual void Attack();
};
