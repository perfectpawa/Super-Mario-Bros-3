#pragma once

#include <vector>

#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

class COWGameObject
{
protected:

	float x;
	float y;

	bool isDeleted;
	bool canGoIn;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }

	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }

	virtual bool CanGoIn() { return canGoIn; }

	COWGameObject();
	COWGameObject(float x, float y, bool canGoIn) :COWGameObject() { this->x = x; this->y = y; this->canGoIn = canGoIn; }


	virtual void Update(DWORD dt, vector<COWGameObject*>* coObjects = NULL) {};
	virtual void Render() = 0;

	~COWGameObject();
};

