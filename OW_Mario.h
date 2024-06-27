#pragma once
#include "OW_GameObject.h"
#include "Animations.h"
#include "AssetIDs.h"

class COWMario: public COWGameObject {
public:
	COWMario(float x, float y, bool canGoIn);
	void Update(DWORD dt, vector<COWGameObject*>* coObjects);
	void Render();
};