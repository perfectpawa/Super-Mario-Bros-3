#pragma once
#include "OW_GameObject.h"
#include "AssetIDs.h"

class COWPortal : public COWGameObject {
protected:
	int sceneId;
	int portalSpriteId;
public:
	COWPortal(float x, float y, bool canGoIn, int portalId);
	void Render();
	int GetSceneId() { return sceneId; }
};