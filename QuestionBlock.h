#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 16

#define QBLOCK_STATE_IDLE 1000
#define QBLOCK_STATE_GET_HIT 1001

#define REWARD_COIN 0
#define REWARD_MUSHROOM 1
#define REWARD_LEAF 2




class CQuestionBlock : public CGameObject {
protected:
	int reward_type;
public:
	CQuestionBlock(float x, float y, int reward_type);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void GetReward();
	void SpawnMusroom();
};