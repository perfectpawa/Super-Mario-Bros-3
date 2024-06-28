#pragma once
#include "UIObject.h"

class CNumberUI : public CUIObject
{
protected:
	int digit;
	int number;
public:
	CNumberUI(float x, float y, int number, int digit);
	virtual void Render();
	void SetNumber(int number) { this->number = number; }
	int GetNumber() { return number; }
};