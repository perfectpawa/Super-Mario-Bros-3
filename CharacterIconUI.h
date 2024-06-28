#pragma once
#include "IconUI.h"

#define TYPE_MARIO 0
#define TYPE_LUIGI 1

class CCharacterIconUI : public CIconUI
{
protected:
	int type;
public:
	CCharacterIconUI(float x, float y, int type);
	virtual void Render();
	void ChangeType(int type) { this->type = type; }
};