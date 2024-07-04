#pragma once

#include "KeyEventHandler.h"
#include "Collision.h"


/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public: 
	CScene(int id, LPCWSTR filePath);

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 

	virtual void SetDefaultPos(float x, float y) {};

	virtual float GetTimeLimit() { return -1; };
	virtual void SetTimeLimit(float timeLimit) {};

	virtual void AddObject(LPGAMEOBJECT obj, int type) = 0;
	virtual void AddEffect(LPEFFECTOBJECT obj) = 0;
	virtual void ChangeBrickCoin(int type) = 0;
	virtual LPGAMEOBJECT GetPlayer() = 0;
	virtual LPOWGAMEOBJECT GetOWPlayer() = 0;

	virtual void FreezeScene(int freezeTime) = 0;
	virtual void GetIsFreeze(bool& isFreeze) = 0;
	
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