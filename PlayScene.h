#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "OW_GameObject.h"

typedef COWGameObject* LPOWGAMEOBJECT;

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> enemyObjs;
	vector<LPGAMEOBJECT> itemObjs;
	vector<LPGAMEOBJECT> terrainObjs;
	vector<LPGAMEOBJECT> frontTerrainObjs;
	vector<LPGAMEOBJECT> tileBackgroundObjs;
	vector<LPGAMEOBJECT> backgroundObjs;
	vector<LPGAMEOBJECT> detectObjs;


	bool isOnOverworldMap = false;
	LPOWGAMEOBJECT OW_player;

	vector<LPOWGAMEOBJECT> OW_pathObjs;



	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
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


	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

