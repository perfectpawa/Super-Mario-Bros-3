#pragma once
#include "OW_GameObject.h"
#include "Animations.h"
#include "AssetIDs.h"

#define MOVE_SPEED	0.1f

class COWMario: public COWGameObject {
protected:
	float start_x;
	float start_y;
	float end_x;
	float end_y;

	int moveHorizontal;
	int moveVertical;
	
	bool isMoving;
	bool isTravel;

	bool wantMove;

	int portalId;

public:
	COWMario(float x, float y, bool canGoIn);
	void Update(DWORD dt, vector<COWGameObject*>* coObjects);
	void Render();
	void Moving(DWORD dt);
	void GetMovDestination(vector<COWGameObject*>* coObjects);
	void CheckEndPointValid(vector<COWGameObject*>* coObjects);

	void MoveHorizontal(int direction) { moveHorizontal = direction; moveVertical = 0; wantMove = true; }
	void MoveVertical(int direction) { moveVertical = direction; moveHorizontal = 0; wantMove = true; }

	void SetTravelPoint(float x, float y) { end_x = x; end_y = y; isTravel = true; }

	void GetInLevel();
};