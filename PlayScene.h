#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "OW_MapHolder.h"
#include "OW_GameObject.h"
#include "BackgroundObject.h"
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
	float timeLimit = 0;


	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OW_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	virtual void AddObject(LPGAMEOBJECT obj, int type);
	virtual void MoveFrontToBack(LPGAMEOBJECT obj);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void Update_OW(DWORD dt);
	virtual void Render_OW();

	virtual void LoadUI();
	virtual void UpdateUI(DWORD dt, float cx, float cy);
	virtual void UpdateUIPosFixedCam();
	virtual void UpdateUIPosFixedCam(float cx, float cy);
	virtual void UpdateUITimeLimit(DWORD dt);
	virtual void UpdateUIPower();
	virtual void UpdateUICoin();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPOWGAMEOBJECT GetOWPlayer() { return OW_player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

