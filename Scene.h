#pragma once
#include "KeyEventHandler.h"

#include <iostream>

#include "Utils.h"
#include "debug.h"

#include "HUD.h"


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_SETTINGS	3

#define MAX_SCENE_LINE 1024

#define LOADING_START_TIME 500
#define LOADING_END_TIME 1000
#define BLACK_SCREEN_ID	-10

using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

class COWGameObject;
typedef COWGameObject * LPOWGAMEOBJECT;

/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

	CHUD* mainHUD;

	//scene setting
	int level_id = -1;

	float timeLimit = -1;

	float camLimitLeft = NULL;
	float camLimitRight = NULL;
	float camLimitTop = NULL;
	float camLimitBottom = NULL;

	float camVerticalFreeZone = NULL;

	//freeze
	BOOLEAN isFreeze = false;
	ULONGLONG freezeTime = -1;
	ULONGLONG freeze_start = -1;

	bool loadingStart = false;
	ULONGLONG loading_start = -1;

	bool loadingEnd = false;
	ULONGLONG loading_end = -1;

	D3DXCOLOR backgroundColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);


	virtual void _ParseSection_OBJECTS(string line) = 0;
	virtual void _ParseSection_SETTINGS(string line);

public: 
	CScene(int id, LPCWSTR filePath);

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;

	virtual void Update(DWORD dt);
	virtual void Render() = 0; 

	virtual void RenderOnFreeze() {};
	virtual void UpdateOnFreeze(DWORD dt) {};

	virtual void RenderLoadingStart();
	virtual void RenderLoadingEnd();
	virtual void RenderBlackScreen(float alpha) {};

	virtual void FreezeScene(ULONGLONG freezeTime);
	virtual void GetIsFreeze(bool& isFreeze) { isFreeze = this->isFreeze; }

	void LoadIntro();
	void LoadOutro();

	virtual void SetDefaultPos(float x, float y) {};

	virtual float GetTimeLimit() { return -1; };
	virtual void SetTimeLimit(float timeLimit) {};

	virtual void LoadUI();
	virtual void UpdateUI(DWORD dt);

	virtual void Clear() {};
	virtual void PurgeDeletedObjects() {};

	virtual LPGAMEOBJECT GetPlayer() { return nullptr; }
	virtual LPOWGAMEOBJECT GetOWPlayer() { return nullptr; }
	

	
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;