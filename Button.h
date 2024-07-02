#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define COUNTDOWN 5000

class CButton : public CGameObject {
protected:
	bool pressed = false;
	ULONGLONG countdown_start = -1;
public:
	CButton(float x, float y);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void Pressing();
	virtual int IsBlocking() { return 0; }

};
