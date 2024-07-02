#pragma once
#include "OW_GameObject.h"
#include "AssetIDs.h"

#define OW_POINT_TYPE_START			00
#define OW_POINT_TYPE_LOCK			10
#define OW_POINT_TYPE_CARD			20
#define OW_POINT_TYPE_MUSHROOM		30
#define OW_POINT_TYPE_BRIDGE		40
#define OW_POINT_TYPE_SMALL_CASTLE	50
#define OW_POINT_TYPE_LOCK_BIG_CASTLE	60




class COWPoint : public COWGameObject {
protected:
	int type;
public:
	COWPoint(float x, float y, bool canGoIn, int type);
	void Render();
};