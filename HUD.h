#pragma once
#include "UIObject.h"
#include "AssetIDs.h"

class CHUD : public CUIObject
{
public:
	CHUD(float x, float y);
	virtual void Render();
};