#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"

#include "Portal.h"
#include "Coin.h"
#include "Brick.h"
#include "QuestionBlock.h"

#include "Platform.h"
#include "ColorBox.h"

#include "Goomba.h"
#include "ParaGoomba.h"

#include "Koopas.h"
#include "Venus.h"

#include "Mario.h"

#include "Mushroom.h"

#include "SpawnCheck.h"
#include "Background.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

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
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* enemyObj = NULL;
	CGameObject* itemObj = NULL;
	CGameObject* terrainObj = NULL;
	CGameObject* frontTerrainObj = NULL;
	CGameObject* backgroundObj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
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
	case OBJECT_TYPE_BREAKABLE_BRICK: enemyObj = new CBrick(x,y); break;
	case OBJECT_TYPE_SPAWN_CHECK: enemyObj = new CSpawnCheck(); break;
	case OBJECT_TYPE_MUSHROOM: enemyObj = new CMushroom(x, y); break;
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
		bool isDirectionColliable = (atoi(tokens[6].c_str()) != 0);
		bool isVertical = (atoi(tokens[7].c_str()) != 0);
		bool isFront = (atoi(tokens[8].c_str()) != 0);
		int sprite_begin = atoi(tokens[9].c_str());
		int sprite_middle = atoi(tokens[10].c_str());
		int sprite_end = atoi(tokens[11].c_str());

		if (isFront) {
			frontTerrainObj = new CPlatform(
				x, y,
				cell_width, cell_height, length, isDirectionColliable, isVertical,
				sprite_begin, sprite_middle, sprite_end
			);
		}
		else {
			terrainObj = new CPlatform(
				x, y,
				cell_width, cell_height, length, isDirectionColliable, isVertical,
				sprite_begin, sprite_middle, sprite_end
			);
		}
		break;
	}

	case OBJECT_TYPE_COLOR_BOX: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int width = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_id_top_left = atoi(tokens[7].c_str());
		int sprite_id_top_middle = atoi(tokens[8].c_str());
		int sprite_id_top_right = atoi(tokens[9].c_str());
		int sprite_id_middle_left = atoi(tokens[10].c_str());
		int sprite_id_middle_middle = atoi(tokens[11].c_str());
		int sprite_id_middle_right = atoi(tokens[12].c_str());
		int sprite_id_bottom_left = atoi(tokens[13].c_str());
		int sprite_id_bottom_middle = atoi(tokens[14].c_str());
		int sprite_id_bottom_right = atoi(tokens[15].c_str());

		terrainObj = new CColorBox(
			x, y,
			cell_width, cell_height,
			width, height,
			sprite_id_top_left, sprite_id_top_middle, sprite_id_top_right,
			sprite_id_middle_left, sprite_id_middle_middle, sprite_id_middle_right,
			sprite_id_bottom_left, sprite_id_bottom_middle, sprite_id_bottom_right
		);
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
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = -1;
		int sprite_end = -1;
		if (length > 1) {
			sprite_middle = atoi(tokens[7].c_str());
			sprite_end = atoi(tokens[8].c_str());
		}

		backgroundObj = new CBackground(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		break;
	}

	case OBJECT_TYPE_TILE_BACKGROUND: {
		int length = atoi(tokens[3].c_str());
		float width = (float)atof(tokens[4].c_str());
		int spriteId = atoi(tokens[5].c_str());
		float posX = x, posY = y;
		for (int i = 0; i < length; i++) {
			CBackground* tileBackgroundObj = new CBackground(
				posX, posY,
				width, 240, 1,
				spriteId, -1, -1
			);
			tileBackgroundObjs.push_back(tileBackgroundObj);
			posX += width;
		}
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

	if (backgroundObj != NULL) {
		backgroundObjs.push_back(backgroundObj);
		backgroundObj->SetPosition(x, y);
	}
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
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
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

	//update terrainObjs
	for (int i = 0; i < terrainObjs.size(); i++)
		terrainObjs[i]->Update(dt, &coObjects);

	//update frontTerrainObjs
	for (int i = 0; i < frontTerrainObjs.size(); i++)
		frontTerrainObjs[i]->Update(dt, &coObjects);

	//update backgroundObjs
	for (int i = 0; i < backgroundObjs.size(); i++)
		backgroundObjs[i]->Update(dt, &coObjects);


	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update player
	player->Update(dt, &coObjects);

	//add player to coObjects
	//coObjects.push_back(player);


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


	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= (float)game->GetBackBufferWidth() / 2;
	cy -= (float)game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;
	if (cy > 0) cy = 0;

	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();

	//for all item in tilebackground, if x of item is < cx, update to x = last item x + width
	float posX, posY;
	tileBackgroundObjs[tileBackgroundObjs.size() - 1]->GetPosition(posX, posY);
	posX += 16;
	for (int i = 0; i < tileBackgroundObjs.size(); i++) {
		float x, y;
		tileBackgroundObjs[i]->GetPosition(x, y);
		if (x < cx - 16) {
			tileBackgroundObjs[i]->SetPosition(posX, y);
			posX += 16;
		}
		else
			break;
	}
	//for last to first, if x of item is > cx + width, update to x = first item x - width
	tileBackgroundObjs[0]->GetPosition(posX, posY);
	posX -= 16;
	float maxPosX = cx + 16 * (tileBackgroundObjs.size() - 1);
	for (int i = (int)tileBackgroundObjs.size() - 1; i >= 0; i--) {
		float x, y;
		tileBackgroundObjs[i]->GetPosition(x, y);
		if (x > maxPosX) {
			tileBackgroundObjs[i]->SetPosition(posX, y);
			posX -= 16;
		}
		else
			break;
	}

	//sort tileBackgroundObjs by x
	sort(tileBackgroundObjs.begin(), tileBackgroundObjs.end(), [](LPGAMEOBJECT a, LPGAMEOBJECT b) {
		float x1, y1, x2, y2;
		a->GetPosition(x1, y1);
		b->GetPosition(x2, y2);
		return x1 < x2;
	});
}

void CPlayScene::Render()
{
	//render tileBackgroundObjs
	for (int i = 0; i < tileBackgroundObjs.size(); i++)
		tileBackgroundObjs[i]->Render();

	//render backgroundObjs
	for (int i = 0; i < backgroundObjs.size(); i++)
		backgroundObjs[i]->Render();

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
}

/*
*	Clear all objects from this scene
*/
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

	//clear backgroundObjs
	for (it = backgroundObjs.begin(); it != backgroundObjs.end(); it++)
	{
		delete (*it);
	}
	backgroundObjs.clear();

	//clear detectObjs
	for (it = detectObjs.begin(); it != detectObjs.end(); it++)
	{
		delete (*it);
	}
	detectObjs.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
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

	//unload backgroundObjs
	for (int i = 0; i < backgroundObjs.size(); i++)
		delete backgroundObjs[i];
	backgroundObjs.clear();

	//unload dectectObjs
	for (int i = 0; i < detectObjs.size(); i++)
		delete detectObjs[i];
	detectObjs.clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

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

	//check in backgroundObjs
	for (it = backgroundObjs.begin(); it != backgroundObjs.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	backgroundObjs.erase(
		std::remove_if(backgroundObjs.begin(), backgroundObjs.end(), CPlayScene::IsGameObjectDeleted),
		backgroundObjs.end());

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
	}
}