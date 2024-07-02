#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"

#include "LevelKeyHandler.h"
#include "OverworldKeyHandler.h"

#pragma region include GameObject
#include "Portal.h"
#include "Coin.h"
#include "Brick.h"
#include "QuestionBlock.h"

#include "Platform.h"
#include "ColorBox.h"
#include "Tube.h"

#include "Goomba.h"
#include "ParaGoomba.h"

#include "Koopas.h"
#include "Venus.h"

#include "Mario.h"

#include "Mushroom.h"

#include "SpawnCheck.h"

#include "OW_Mario.h"
#include "OW_Path.h"
#include "OW_Terrain.h"
#include "OW_Portal.h"
#include "OW_Point.h"

#pragma endregion

using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_SETTINGS	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	OW_player = NULL;
	OW_mapHolder = NULL;
	mainHUD = NULL;
	key_handler = new CLevelKeyHandler(this);
}

#pragma region Parse Section
void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	//DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* enemyObj = NULL;
	CGameObject* itemObj = NULL;
	CGameObject* terrainObj = NULL;
	CGameObject* frontTerrainObj = NULL;
	CBackgroundObject* backgroundObj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: {
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		/*obj = new CMario(x,y);
		player = (CMario*)obj;  */

		player = new CMario(x, y);
		player->SetPosition(x, y);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: {
		int type = atoi(tokens[3].c_str());
		if (type == 1) enemyObj = new CParaGoomba(x, y);
		else enemyObj = new CGoomba(x, y);
		break;
	}
	case OBJECT_TYPE_KOOPAS: {
		int type = atoi(tokens[3].c_str());
		enemyObj = new CKoopas(x, y, type); break;
	}
	case OBJECT_TYPE_BRICK: {
		int type = atoi(tokens[3].c_str());
		int spriteId = -1;
		if (tokens.size() == 5) {
			spriteId = atoi(tokens[4].c_str());
		}
		terrainObj = new CBrick(x, y, type, spriteId);
		break;

	}
	case OBJECT_TYPE_SPAWN_CHECK: enemyObj = new CSpawnCheck(); break;
	case OBJECT_TYPE_MUSHROOM: itemObj = new CMushroom(x, y); break;
	case OBJECT_TYPE_VENUS: enemyObj = new CVenus(x, y); break;
	case OBJECT_TYPE_QUESTION_BLOCK: {
		int type = atoi(tokens[3].c_str());
		frontTerrainObj = new CQuestionBlock(x, y, type);
		break;
	}
	case OBJECT_TYPE_COIN: itemObj = new CCoin(x, y); break;
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = sprite_begin;
		int sprite_end = sprite_begin;
		bool isDirectionColliable = false;
		bool isVertical = false;
		bool isFront = false;

		if (tokens.size() >= 9)
		{
			sprite_middle = atoi(tokens[7].c_str());
			sprite_end = atoi(tokens[8].c_str());
		}
		if (tokens.size() == 12) {
			isDirectionColliable = (atoi(tokens[9].c_str()) == 1);
			isVertical = (atoi(tokens[10].c_str()) == 1);
			isFront = (atoi(tokens[11].c_str()) == 1);
		}


		if (isFront) {
			frontTerrainObj = new CPlatform(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end,
				isDirectionColliable, isVertical
			);
		}
		else {
			terrainObj = new CPlatform(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end,
				isDirectionColliable, isVertical
			);
		}
		break;
	}
	case OBJECT_TYPE_COLOR_BOX: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int color_id = atoi(tokens[7].c_str());

		terrainObj = new CColorBox(
			x, y,
			cell_width, cell_height,
			width, height,
			color_id
		);
		break;

	}
	case OBJECT_TYPE_TUBE: {
		int length = atoi(tokens[3].c_str());
		bool isUpsideDown = false;
		int type = 0;
		if (tokens.size() == 6) {
			isUpsideDown = (atoi(tokens[4].c_str()) == 1);
			type = atoi(tokens[5].c_str());
		}

		terrainObj = new CTube(x, y, length, isUpsideDown, type);
		break;
	}
	case OBJECT_TYPE_GROUND: {
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());

		CGameObject* groundObj;

		groundObj = new CPlatform(
			x, y - 6,
			16, 6, width,
			ID_SPRITE_OVERGROUND + 1, ID_SPRITE_OVERGROUND + 2, ID_SPRITE_OVERGROUND + 3,
			0, 0
		);

		terrainObjs.push_back(groundObj);

		if (height >= 2) {
			groundObj = new CPlatform(
				x, y + 4,
				16, 16, width,
				ID_SPRITE_UNDERGROUND + 1, ID_SPRITE_UNDERGROUND + 2, ID_SPRITE_UNDERGROUND + 3,
				0, 0
			);

			terrainObjs.push_back(groundObj);
		}

		if (height >= 3) {
			for (int i = 1; i < height - 1; i++) {
				groundObj = new CPlatform(
					x, y + 4 + 16 * i,
					16, 16, width,
					ID_SPRITE_DEEPERROUND + 1, ID_SPRITE_DEEPERROUND + 2, ID_SPRITE_DEEPERROUND + 3,
					0, 0
				);
			}

			terrainObjs.push_back(groundObj);
		}

		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		terrainObj = new CPortal(x, y, r, b, scene_id);
		break;

	}
	case OBJECT_TYPE_BACKGROUND: {
		int type = atoi(tokens[3].c_str());
		int length = 1;

		if (tokens.size() == 5) {
			length = atoi(tokens[4].c_str());
		}
		backgroundObj = new CBackgroundObject(x, y, type, length);
		backgroundObjs.push_back(backgroundObj);
		break;

	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	if (enemyObj != NULL) {
		enemyObjs.push_back(enemyObj);
		enemyObj->SetPosition(x, y);
	}

	if (itemObj != NULL) {
		itemObjs.push_back(itemObj);
		itemObj->SetPosition(x, y);
	}

	if (terrainObj != NULL) {
		terrainObjs.push_back(terrainObj);
		terrainObj->SetPosition(x, y);
	}

	if (frontTerrainObj != NULL) {
		frontTerrainObjs.push_back(frontTerrainObj);
		frontTerrainObj->SetPosition(x, y);
	}
}

void CPlayScene::_ParseSection_SETTINGS(string line) {
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens[0] == "time") {
		timeLimit = (float)atof(tokens[1].c_str());
	}

	if (tokens[0] == "background_color") {
		float r = (float)atof(tokens[1].c_str());
		float g = (float)atof(tokens[2].c_str());
		float b = (float)atof(tokens[3].c_str());
		DebugOut(L"Background color: %f %f %f\n", r, g, b);
		CGame::GetInstance()->SetBackgroundColor(D3DXCOLOR(r / 255.0f, g / 255.0f, b / 255.0f, 0.0f));
	}

	if (tokens[0] == "cam_limit") {
		if(tokens.size() > 1) camLimitLeft = (float)atof(tokens[1].c_str());
		if (tokens.size() > 2) camLimitRight = (float)atof(tokens[2].c_str());
		if (tokens.size() > 3) camLimitTop = (float)atof(tokens[3].c_str());
		if (tokens.size() > 4) camLimitBottom = (float)atof(tokens[4].c_str());
	}
}

void CPlayScene::_ParseSection_OW_OBJECTS(string line) {
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());


	switch (object_type) {
	case OW_OBJ_TYPE_MARIO: {
		if (OW_player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		OW_player = new COWMario(x, y, true);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OW_OBJ_TYPE_MAP_HOLDER: {
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		OW_mapHolder = new COWMapHolder(x, y, width, height);
		break;
	}
	case OW_OBJ_TYPE_PATH: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		bool isVertical = (atoi(tokens[4].c_str()) == 1);
		bool haveCoin = (atoi(tokens[5].c_str()) == 1);
		bool haveTurn = (atoi(tokens[6].c_str()) == 1);
		COWPath* path = new COWPath(x, y, isGoIn, isVertical, haveCoin, haveTurn);
		OW_pathObjs.push_back(path);
		break;
	}
	case OW_OBJ_TYPE_TERRAIN: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		int type = atoi(tokens[4].c_str());

		int sub_type = 0;
		if (tokens.size() > 5) {
			sub_type = atoi(tokens[5].c_str());
		}

		COWTerrain* terrain = new COWTerrain(x, y, isGoIn, type, sub_type);
		OW_terrainObjs.push_back(terrain);
		break;
	}
	case OW_OBJ_TYPE_PORTAL: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		int portalId = atoi(tokens[4].c_str());
		COWPortal* portal = new COWPortal(x, y, isGoIn, portalId);
		OW_portalObjs.push_back(portal);
		break;
	}
	case OW_OBJ_TYPE_POINT: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		int type = atoi(tokens[4].c_str());
		COWPoint* point = new COWPoint(x, y, isGoIn, type);
		OW_pointObjs.push_back(point);
		break;
	}
	}

}

#pragma endregion

#pragma region Load
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OVERWORLD]") {
			isOnOverworldMap = true;
			CGame::GetInstance()->SetCamPos(-16, -16);
			key_handler = new COverworldKeyHandler(this);
			continue;
		};
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[UI]") { LoadUI(); continue; }
		if (line == "[SETTINGS]") { section = SCENE_SECTION_SETTINGS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		if (isOnOverworldMap) {
			switch (section)
			{
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OW_OBJECTS(line); break;
			case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
			}
		}
		else {
			switch (section)
			{
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
			}
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::LoadUI()
{
	DebugOut(L"[INFO] Start loading UI\n");
	mainHUD = new CHUD(0, 0);

	UpdateUIPosFixedCam();
}

void CPlayScene::Unload()
{
	//unload enemyObjs
	for (int i = 0; i < enemyObjs.size(); i++)
		delete enemyObjs[i];
	enemyObjs.clear();

	//unload itemObjs
	for (int i = 0; i < itemObjs.size(); i++)
		delete itemObjs[i];
	itemObjs.clear();

	//unload terrainObjs
	for (int i = 0; i < terrainObjs.size(); i++)
		delete terrainObjs[i];
	terrainObjs.clear();

	//unload frontTerrainObjs
	for (int i = 0; i < frontTerrainObjs.size(); i++)
		delete frontTerrainObjs[i];
	frontTerrainObjs.clear();

	//unload dectectObjs
	for (int i = 0; i < detectObjs.size(); i++)
		delete detectObjs[i];
	detectObjs.clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

#pragma endregion

#pragma region Update
void CPlayScene::Update(DWORD dt)
{
	if (isOnOverworldMap) {
		Update_OW(dt);
		return;

	}

	vector<LPGAMEOBJECT> coObjects;
	//push back all objects in enemyObjs and terrainObjs to coObjects
	for (int i = 0; i < enemyObjs.size(); i++)
		coObjects.push_back(enemyObjs[i]);
	for (int i = 0; i < itemObjs.size(); i++)
		coObjects.push_back(itemObjs[i]);
	for (int i = 0; i < terrainObjs.size(); i++)
		coObjects.push_back(terrainObjs[i]);
	for (int i = 0; i < frontTerrainObjs.size(); i++)
		coObjects.push_back(frontTerrainObjs[i]);
	for (int i = 0; i < detectObjs.size(); i++)
		coObjects.push_back(detectObjs[i]);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update player
	player->Update(dt, &coObjects);

	//update detect objects, coObjects of dectect only include player
	vector<LPGAMEOBJECT> detectCoObjects;
	detectCoObjects.push_back(player);
	for (int i = 0; i < detectObjs.size(); i++) {
		detectObjs[i]->Update(dt, &detectCoObjects);
	}

	//update enemyObjs
	for (int i = 0; i < enemyObjs.size(); i++) {
		if (dynamic_cast<CSpawnCheck*>(enemyObjs[i])) {
			break;
		}
		enemyObjs[i]->Update(dt, &coObjects);
	}

	//update itemObjs
	for (int i = 0; i < itemObjs.size(); i++)
		itemObjs[i]->Update(dt, &coObjects);

	CamPosFollowPlayer();

	UpdateUI(dt);


	PurgeDeletedObjects();
}

void CPlayScene::Update_OW(DWORD dt) {
	vector<COWGameObject*> coObjects;

	//check item in OW_pathObjs
	for (int i = 0; i < OW_pathObjs.size(); i++) {
		if (!OW_pathObjs[i]->CanGoIn()) continue;
		coObjects.push_back(OW_pathObjs[i]);
	}

	//check item in OW_pointObjs
	for (int i = 0; i < OW_pointObjs.size(); i++) {
		if (!OW_pointObjs[i]->CanGoIn()) continue;
		coObjects.push_back(OW_pointObjs[i]);
	}

	//check item in OW_portalObjs
	for (int i = 0; i < OW_portalObjs.size(); i++) {
		if (!OW_portalObjs[i]->CanGoIn()) continue;
		coObjects.push_back(OW_portalObjs[i]);
	}

	OW_player->Update(dt, &coObjects);
}

#pragma endregion

#pragma region Render
void CPlayScene::Render()
{
	if (isOnOverworldMap) {
		Render_OW();
		return;
	}

	//render backgroundObjs
	for (int i = 0; i < backgroundObjs.size(); i++) {
		backgroundObjs[i]->Render();
	}

	//render terrainObjs
	for (int i = 0; i < terrainObjs.size(); i++) {
		terrainObjs[i]->Render();
	}

	//render enemyObjs
	for (int i = 0; i < enemyObjs.size(); i++)
		enemyObjs[i]->Render();

	//render detectObjs
	for (int i = 0; i < detectObjs.size(); i++)
		detectObjs[i]->Render();

	//render itemObjs
	for (int i = 0; i < itemObjs.size(); i++)
		itemObjs[i]->Render();

	//render frontTerrainObjs
	for (int i = 0; i < frontTerrainObjs.size(); i++)
		frontTerrainObjs[i]->Render();

	//render player
	player->Render();

	//render hud
	if (mainHUD != NULL) mainHUD->Render();
}

void CPlayScene::Render_OW() {

	OW_mapHolder->Render();

	for (int i = 0; i < OW_pathObjs.size(); i++) {
		OW_pathObjs[i]->Render();
	}

	for (int i = 0; i < OW_terrainObjs.size(); i++) {
		OW_terrainObjs[i]->Render();
	}

	for (int i = 0; i < OW_portalObjs.size(); i++) {
		OW_portalObjs[i]->Render();
	}

	for (int i = 0; i < OW_pointObjs.size(); i++) {
		OW_pointObjs[i]->Render();
	}

	OW_player->Render();

	if (mainHUD != NULL) mainHUD->Render();
}

#pragma endregion

#pragma region Clean Up
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;

	//clear enemyObjs
	for (it = enemyObjs.begin(); it != enemyObjs.end(); it++)
	{
		delete (*it);
	}
	enemyObjs.clear();

	//clear itemObjs
	for (it = itemObjs.begin(); it != itemObjs.end(); it++)
	{
		delete (*it);
	}
	itemObjs.clear();

	//clear terrainObjs
	for (it = terrainObjs.begin(); it != terrainObjs.end(); it++)
	{
		delete (*it);
	}
	terrainObjs.clear();

	//clear frontTerrainObjs
	for (it = frontTerrainObjs.begin(); it != frontTerrainObjs.end(); it++)
	{
		delete (*it);
	}
	frontTerrainObjs.clear();

	//clear detectObjs
	for (it = detectObjs.begin(); it != detectObjs.end(); it++)
	{
		delete (*it);
	}
	detectObjs.clear();
}

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	//check in enemyObjs
	for (it = enemyObjs.begin(); it != enemyObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	enemyObjs.erase(
		std::remove_if(enemyObjs.begin(), enemyObjs.end(), CPlayScene::IsGameObjectDeleted),
		enemyObjs.end());

	//check in itemObjs
	for (it = itemObjs.begin(); it != itemObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	itemObjs.erase(
		std::remove_if(itemObjs.begin(), itemObjs.end(), CPlayScene::IsGameObjectDeleted),
		itemObjs.end());

	//check in terrainObjs
	for (it = terrainObjs.begin(); it != terrainObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	terrainObjs.erase(
		std::remove_if(terrainObjs.begin(), terrainObjs.end(), CPlayScene::IsGameObjectDeleted),
		terrainObjs.end());

	//check in frontTerrainObjs
	for (it = frontTerrainObjs.begin(); it != frontTerrainObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	frontTerrainObjs.erase(
		std::remove_if(frontTerrainObjs.begin(), frontTerrainObjs.end(), CPlayScene::IsGameObjectDeleted),
		frontTerrainObjs.end());

	//check in detectObjs
	for (it = detectObjs.begin(); it != detectObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	detectObjs.erase(
		std::remove_if(detectObjs.begin(), detectObjs.end(), CPlayScene::IsGameObjectDeleted),
		detectObjs.end());

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
}

#pragma endregion

#pragma region Utils
bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::CamPosFollowPlayer() {
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= (float)game->GetBackBufferWidth() / 2;
	cy -= (float)game->GetBackBufferHeight() / 2;

	if(camLimitLeft != NULL && cx < camLimitLeft) cx = camLimitLeft;
	if (camLimitRight != NULL && cx > camLimitRight - game->GetBackBufferWidth()) cx = camLimitRight - game->GetBackBufferWidth();

	if(camLimitBottom != NULL && cy > camLimitBottom) cy = camLimitBottom;

	CGame::GetInstance()->SetCamPos(cx, cy);
}

void CPlayScene::AddObject(LPGAMEOBJECT obj, int type)
{
	switch (type)
	{
	case OBJECT_TYPE_MUSHROOM:
		itemObjs.push_back(obj);
		break;
	case OBJECT_TYPE_COIN:
		itemObjs.push_back(obj);
		break;
	case OBJECT_TYPE_LEAF:
		itemObjs.push_back(obj);
		break;
	case OBJECT_TYPE_VENUS_FIRE_BALL:
		detectObjs.push_back(obj);
		break;
	}
}

void CPlayScene::MoveFrontToBack(LPGAMEOBJECT obj)
{
	//remove obj from frontTerrainObjs
	vector<LPGAMEOBJECT>::iterator it = find(frontTerrainObjs.begin(), frontTerrainObjs.end(), obj);
	if (it != frontTerrainObjs.end())
		frontTerrainObjs.erase(it);

	//add obj to terrainObjs
	terrainObjs.push_back(obj);
}

void CPlayScene::UpdateUI(DWORD dt) {
	if (mainHUD == NULL) return;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	UpdateUIPosFixedCam(cx, cy);

	UpdateUITimeLimit(dt);
	UpdateUIPower();
	UpdateUICoin();
}

void CPlayScene::UpdateUIPosFixedCam() {
	float hud_x, hud_y, cam_x, cam_y;

	CGame* game = CGame::GetInstance();
	game->GetCamPos(cam_x, cam_y);
	hud_x = (float)cam_x + game->GetBackBufferWidth() / 2.0f - 16 * 2.5f;
	hud_y = (float)cam_y + game->GetBackBufferHeight() - 16 * 1.75f;

	mainHUD->SetPosition(hud_x, hud_y);
}

void CPlayScene::UpdateUIPosFixedCam(float cx, float cy) {
	float hud_x, hud_y;

	hud_x = cx + 16 * 5;
	hud_y = cy + 16 * 11.75f;

	mainHUD->SetPosition(hud_x, hud_y);
}

void CPlayScene::UpdateUITimeLimit(DWORD dt) {
	if (timeLimit <= 0) {
		timeLimit = 0;
		player->SetState(MARIO_STATE_DIE);
	}
	else {
		timeLimit -= dt / 1000.0f;
	}
	mainHUD->SetTime((int)timeLimit);
}

void CPlayScene::UpdateUIPower() {
	int power = 0;
	CMario* mario = dynamic_cast<CMario*>(player);
	if (mario != NULL) {
		mario->GetPowerSprintState(power);
	}
	mainHUD->SetPower(power);
}

void CPlayScene::UpdateUICoin() {
	int coin = 0;
	CMario* mario = dynamic_cast<CMario*>(player);
	if (mario != NULL) {
		mario->GetCoin(coin);
	}
	mainHUD->SetCoin(coin);
}
#pragma endregion

