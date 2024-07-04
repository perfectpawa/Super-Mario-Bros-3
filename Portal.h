#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	float width;
	float height;

	int scene_id;	// target scene to switch to 
	int keyCode;	// key code to trigger scene switching

	bool isMainPortal; // need this bc will have pseudo portal for the main portal

	bool haveStartPos; // check if have start position to spawn player after switching scene
	float start_x, start_y; // position to spawn player after switching scene

	int dir_x, dir_y; // direction to animate player when switching scene
	
public:
	CPortal(
		float x, float y, float width, float height,
		bool isMainPortal = false,
		int scene_id = -1, int keyCode = -1,
		int dir_x = 0, int dir_y = 0,
		bool haveStartPos = false, float start_x = 0, float start_y = 0
	);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox();
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }

	bool IsMainPortal() { return isMainPortal; }

	int GetKeyCode() { return keyCode; }
	void SwitchScene();

	void GetDirection(int& dx, int& dy) { dx = dir_x; dy = dir_y; }
};