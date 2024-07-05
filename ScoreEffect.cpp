#include "ScoreEffect.h"


CScoreEffect::CScoreEffect(float x, float y, int score) : CEffectObject(x, y)
{
	vy = -EFFECT_SPEED;
	minPosy = y - 8;
	this->score = score;

	SaveFile::GetInstance()->AddScore(score);
}

void CScoreEffect::Render()
{
	int spriteId = ID_SPRITE_EFFECT_POINT + score;

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y);
}

void CScoreEffect::Update(DWORD dt)
{
	y += vy * dt;
	x += vy / 2 * dt;

	if (y <= minPosy)
	{
		this->Delete();
		return;
	}
}

