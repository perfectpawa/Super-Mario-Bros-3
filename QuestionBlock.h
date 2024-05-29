#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 16

#define QBLOCK_STATE_IDLE 1000
#define QBLOCK_STATE_BOUND_UP 1001
#define QBLOCK_STATE_BOUND_DOWN 1002
#define QBLOCK_STATE_EMPTY 1003

#define REWARD_COIN 0
#define REWARD_POWERUP 1

#define QBLOCK_BOUND_SPEED 0.1f



class CQuestionBlock : public CGameObject {
protected:
	int reward_type;
	float boundPosY;
	float idlePosY;
public:
	CQuestionBlock(float x, float y, int reward_type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetRewardType() { return reward_type; }
	void GetReward();
	void SetState(int state);
	void SpawnMusroom();
	void SpawnCoinEffect();
};