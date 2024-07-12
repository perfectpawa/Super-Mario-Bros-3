#pragma once
#include "OW_GameObject.h"

#define	BOSS_MOVE_SPEED	0.02f;

class COWBoss : public COWGameObject {
protected:
	float left_x;
	float left_y;
	float right_x;
	float right_y;

	float vx;
	float vy;

public:
	COWBoss(float left_x, float left_y, float right_x, float right_y);
	void Update(DWORD dt, vector<COWGameObject*>* coObjects);
	void Render();

};