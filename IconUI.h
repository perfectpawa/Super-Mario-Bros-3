#pragma once
#include "UIObject.h"

class CIconUI : public CUIObject
{
protected:
	int iconID;
	bool haveAni;
public:
	CIconUI(float x, float y, int iconID, bool haveAni);
	virtual void Render();
};