#include "QuestionBlock.h"
#include "Mario.h"
#include "Mushroom.h"

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_SPRITE_QUESTION_BLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_BBOX_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::SpawnMusroom()
{
	CMushroom* mushroom = new CMushroom(x, y - 16);
	CGame::GetInstance()->GetCurrentScene()->AddObject(mushroom, 3);
}