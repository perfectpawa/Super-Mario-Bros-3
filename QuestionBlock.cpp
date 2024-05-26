#include "QuestionBlock.h"
#include "Mario.h"
#include "Mushroom.h"

CQuestionBlock::CQuestionBlock(float x, float y, int reward_type) : CGameObject(x, y)
{
	this->reward_type = reward_type;
	SetState(QBLOCK_STATE_IDLE);
}

void CQuestionBlock::Render()
{
	int aniId = ID_ANI_QUESTION_BLOCK;

	if(state == QBLOCK_STATE_GET_HIT)
		aniId = ID_ANI_QUESTION_BLOCK_HIT;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_BBOX_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::GetReward()
{
	switch (reward_type)
	{
	case REWARD_COIN:
		break;
	case REWARD_MUSHROOM:
		SpawnMusroom();
		break;
	case REWARD_LEAF:
		break;
	}
}

void CQuestionBlock::SpawnMusroom()
{
	CMushroom* mushroom = new CMushroom(x, y - 16);
	CGame::GetInstance()->GetCurrentScene()->AddObject(mushroom, 3);
}