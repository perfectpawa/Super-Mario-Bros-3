#pragma once
#include "EffectObject.h"

class CTextEffect : public CEffectObject
{
protected:
	string text;
	int spriteId;
	int offset;
public:
	CTextEffect(float x, float y, string text,int spriteId = -1, int offset = 0);
	void Render();
	void Update(DWORD dt);
};