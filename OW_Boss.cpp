#include "OW_Boss.h"
#include "Animations.h"

COWBoss::COWBoss(float left_x, float left_y, float right_x, float right_y) : COWGameObject(right_x, right_y, false) {
	this->left_x = left_x;
	this->left_y = left_y;
	this->right_x = right_x;
	this->right_y = right_y;

	this->vx = 0;
	this->vy = 0;
}

void COWBoss::Update(DWORD dt, vector<COWGameObject*>* coObjects) {
	if (x >= right_x) {
		vx = -BOSS_MOVE_SPEED;
	}
	if (x <= left_x) {
		vx = BOSS_MOVE_SPEED;
	}

	x += vx * dt;

}

void COWBoss::Render() {
	int aniId = ID_ANI_OW_BOSS_MOVE_LEFT;

	if (vx > 0) aniId = ID_ANI_OW_BOSS_MOVE_RIGHT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}