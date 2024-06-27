#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"

using namespace std;

class CUIObject
{
protected:
	float x;
	float y;
	int spriteID;


public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }


	CUIObject();
	CUIObject(float x, float y, int spriteID) :CUIObject() { this->x = x; this->y = y; this->spriteID = spriteID; }


	virtual void Render();
	~CUIObject();
};