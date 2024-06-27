#pragma once
#include "OW_GameObject.h"
#include "AssetIDs.h"

#define OW_TERRAIN_TYPE_GRASS 0
#define OW_TERRAIN_TYPE_ROCK 1
#define OW_TERRAIN_TYPE_WATER 2

class COWTerrain : public COWGameObject {
protected:
	int type;
	int sub_type;
public:
	COWTerrain(float x, float y, bool canGoIn, int type, int sub_type);
	void Render();
};