#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "BackgroundObject.h"
#include "EffectObject.h"
#include "HUD.h"

#define VIEWPORT_WIDTH 528

#define CAM_SHAKE_TIME 200

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> enemyObjs;
	vector<LPGAMEOBJECT> itemObjs;
	vector<LPGAMEOBJECT> terrainObjs;
	vector<LPGAMEOBJECT> frontTerrainObjs;
	vector<LPGAMEOBJECT> detectObjs;
	vector<LPGAMEOBJECT> attackObjs;

	vector<LPGAMEOBJECT> platformObjs;
	vector<LPGAMEOBJECT> tubeObjs;


	vector<LPGAMEOBJECT> brickCoins;
	vector<LPGAMEOBJECT> coinBricks;

	vector<LPEFFECTOBJECT> effectObjs;

	vector<LPGAMEOBJECT> barrierObjs;

	vector<CBackgroundObject*> backgroundObjs;

	bool firstRender = false;

	bool isCamShaking = false;
	ULONGLONG camShake_start = -1;

	void _ParseSection_OBJECTS(string line);

	virtual void CamPosFollowPlayer();

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void SetDefaultPos(float x, float y);

	virtual float GetTimeLimit() { return timeLimit; }
	virtual void SetTimeLimit(float timeLimit) { this->timeLimit = timeLimit; }

	virtual void RenderOnFreeze();
	virtual void UpdateOnFreeze(DWORD dt);

	virtual void AddObject(LPGAMEOBJECT obj, int type);
	virtual void AddEffect(LPEFFECTOBJECT obj);
	virtual void ChangeBrickCoin(int type);

	virtual void LoadUI();
	virtual void UpdateUI(DWORD dt);
	virtual void UpdateUIPosFixedCam();
	virtual void UpdateUIPosFixedCam(float cx, float cy);
	virtual void UpdateUITimeLimit(DWORD dt);
	virtual void UpdateUIPower();

	void CamSkake() { this->isCamShaking = true; this->camShake_start = GetTickCount64(); }

	bool InPlayerViewPort(float x);

	LPGAMEOBJECT GetPlayer() { return player; }

	virtual void Clear();
	void ClearGameObject(vector<LPGAMEOBJECT>& objs);
	void ClearEffectObject(vector<LPEFFECTOBJECT>& objs);
	void ClearBackgroundObject(vector<CBackgroundObject*>& objs);

	virtual void PurgeDeletedObjects();
	void PurgeDeletedGameObjects(vector<LPGAMEOBJECT>& objs);
	void PurgeDeletedEffectObjects(vector<LPEFFECTOBJECT>& objs);


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	static bool IsEffectObjectDeleted(const LPEFFECTOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

