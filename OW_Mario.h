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
	void GetMoveDestination(vector<COWGameObject*>* coObjects);

	bool CheckValid(float x, float y, vector<COWGameObject*>* coObjects, COWGameObject*& obj);

	void MoveHorizontal(int direction) { 
		if (isMoving) return;
		moveHorizontal = direction; moveVertical = 0; wantMove = true; 
	}
	void MoveVertical(int direction) { 
		if (isMoving) return;
		moveVertical = direction; moveHorizontal = 0; wantMove = true; 
	}

	void SetTravelPoint(float x, float y) { 
		start_x = this->x; start_y = this->y;
		end_x = x; end_y = y; isTravel = true; 
	}

	void GetInLevel();
};