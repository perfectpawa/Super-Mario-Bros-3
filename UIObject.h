#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

using namespace std;

class CUIObject
{
protected:
	float x;
	float y;


public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }


	CUIObject();
	CUIObject(float x, float y) :CUIObject() { this->x = x; this->y = y;}


	virtual void Render() = 0;
	~CUIObject();
};