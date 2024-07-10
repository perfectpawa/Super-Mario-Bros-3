#pragma once
#include "OW_GameObject.h"
#include "AssetIDs.h"

class COWPath: public COWGameObject {
protected:
	bool isVertical;
	bool haveTurn;
	bool isPoint = false;
public:
	COWPath(float x, float y, bool canGoIn, bool isPoint, bool isVertical, bool haveTurn);
	void Render();
	bool IsPoint() { return isPoint; }
};