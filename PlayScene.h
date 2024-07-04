#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "OW_MapHolder.h"
#include "OW_GameObject.h"
#include "BackgroundObject.h"
#include "EffectObject.h"
#include "HUD.h"

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

	vector<LPGAMEOBJECT> brickCoins;
	vector<LPGAMEOBJECT> coinBricks;

	vector<LPEFFECTOBJECT> effectObjs;

	vector<LPGAMEOBJECT> barrierObjs;

	bool isOnOverworldMap = false;
	LPOWGAMEOBJECT OW_player;
	COWMapHolder* OW_mapHolder;
	vector<LPOWGAMEOBJECT> OW_pathObjs;
	vector<LPOWGAMEOBJECT> OW_terrainObjs;
	vector<LPOWGAMEOBJECT> OW_portalObjs;
	vector<LPOWGAMEOBJECT> OW_pointObjs;

	vector<CBackgroundObject*> backgroundObjs;

	CHUD* mainHUD;

	//scene setting
	float timeLimit = -1;

	float camLimitLeft = NULL;
	float camLimitRight = NULL;
	float camLimitTop = NULL;
	float camLimitBottom = NULL;

	float camVerticalFreeZone = NULL;
	
	//
	BOOLEAN isFreeze = false;
	ULONGLONG freezeTime = -1;
	ULONGLONG freeze_start = -1;


	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OW_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	virtual void AddObject(LPGAMEOBJECT obj, int type);
	virtual void AddEffect(LPEFFECTOBJECT obj);
	virtual void ChangeBrickCoin(int type);

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

	virtual void FreezeScene(int freezeTime);
	virtual void GetIsFreeze(bool& isFreeze) { isFreeze = this->isFreeze; }

	virtual void Update_OW(DWORD dt);
	virtual void Render_OW();

	virtual void LoadUI();
	virtual void UpdateUI(DWORD dt);
	virtual void UpdateUIPosFixedCam();
	virtual void UpdateUIPosFixedCam(float cx, float cy);
	virtual void UpdateUITimeLimit(DWORD dt);
	virtual void UpdateUIPower();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPOWGAMEOBJECT GetOWPlayer() { return OW_player; }

	void Clear();
	void ClearGameObject(vector<LPGAMEOBJECT>& objs);
	void ClearEffectObject(vector<LPEFFECTOBJECT>& objs);
	void ClearBackgroundObject(vector<CBackgroundObject*>& objs);

	void PurgeDeletedObjects();
	void PurgeDeletedGameObjects(vector<LPGAMEOBJECT>& objs);
	void PurgeDeletedEffectObjects(vector<LPEFFECTOBJECT>& objs);


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	static bool IsEffectObjectDeleted(const LPEFFECTOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

