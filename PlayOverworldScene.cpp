#include "PlayOverworldScene.h"

#include "OverworldKeyHandler.h"


CPlayOverworldScene::CPlayOverworldScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	player = NULL;
	mapHolder = NULL;
	mainHUD = NULL;
	key_handler = new COverworldKeyHandler(this);
}

void CPlayOverworldScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());


	switch (object_type) {
	case OW_OBJ_TYPE_MARIO: {
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}

		player = new COWMario(x, y, true);

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OW_OBJ_TYPE_MAP_HOLDER: {
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		mapHolder = new COWMapHolder(x, y, width, height);
		break;
	}
	case OW_OBJ_TYPE_PATH: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		bool isVertical = (atoi(tokens[4].c_str()) == 1);
		bool haveTurn = (atoi(tokens[5].c_str()) == 1);

		bool isPoint = isGoIn;

		bool levelBlock = 0;

		if (tokens.size() == 7) {
			levelBlock = (atoi(tokens[6].c_str()) == 1);
		}

		if(levelBlock != 0 && !SaveFile::GetInstance()->isLevelHasComplete(levelBlock)) isGoIn = false;


		COWPath* path = new COWPath(x, y, isGoIn, isPoint, isVertical, haveTurn);
		pathObjs.push_back(path);

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
		terrainObjs.push_back(terrain);
		break;
	}
	case OW_OBJ_TYPE_PORTAL: {
		int portalId = atoi(tokens[3].c_str());

		//check is level has complete
		if (SaveFile::GetInstance()->isLevelHasComplete(portalId)) {
			COWPoint* levelCompleted = new COWPoint(x, y, true, OW_POINT_TYPE_LEVEL_COMPLETED);
			pointObjs.push_back(levelCompleted);
		}
		else {
			COWPortal* portal = new COWPortal(x, y, true, portalId);
			portalObjs.push_back(portal);
		}

		break;
	}
	case OW_OBJ_TYPE_POINT: {
		bool isGoIn = (atoi(tokens[3].c_str()) == 1);
		int type = atoi(tokens[4].c_str());
		COWPoint* point = new COWPoint(x, y, isGoIn, type);
		pointObjs.push_back(point);
		break;
	}
	}

}

void CPlayOverworldScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	CGame::GetInstance()->SetCamPos(-16, -16);
	key_handler = new COverworldKeyHandler(this);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[UI]") { LoadUI(); continue; }
		if (line == "[SETTINGS]") { section = SCENE_SECTION_SETTINGS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
			case SCENE_SECTION_ASSETS: LoadVisual::GetInstance()->_ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		}
	}

	f.close();

	CGame::GetInstance()->SetBackgroundColor(backgroundColor);

	LoadSave();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayOverworldScene::LoadSave()
{
	SaveFile* saveFile = SaveFile::GetInstance();
	float default_x = 0, default_y = 0;
	saveFile->GetLastStand(default_x, default_y);
	player->SetPosition(default_x, default_y);
}

void CPlayOverworldScene::Unload()
{
	isFreeze = false;

	if(player != NULL)
	{
		delete player;
		player = NULL;
	}

	if (mapHolder != NULL)
	{
		delete mapHolder;
		mapHolder = NULL;
	}

	if (mainHUD != NULL)
	{
		delete mainHUD;
		mainHUD = NULL;
	}

	for (size_t i = 0; i < pathObjs.size(); i++) delete pathObjs[i];
	pathObjs.clear();

	for (size_t i = 0; i < terrainObjs.size(); i++) delete terrainObjs[i];
	terrainObjs.clear();

	for (size_t i = 0; i < portalObjs.size(); i++) delete portalObjs[i];
	portalObjs.clear();

	for (size_t i = 0; i < pointObjs.size(); i++) delete pointObjs[i];
	pointObjs.clear();

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayOverworldScene::Update(DWORD dt)
{
	CScene::Update(dt);

	vector<COWGameObject*> coObjects;

	//check item in OW_pathObjs
	for (int i = 0; i < pathObjs.size(); i++) {
		coObjects.push_back(pathObjs[i]);
	}

	//check item in OW_pointObjs
	for (int i = 0; i < pointObjs.size(); i++) {
		if (!pointObjs[i]->CanGoIn()) continue;
		coObjects.push_back(pointObjs[i]);
	}

	//check item in OW_portalObjs
	for (int i = 0; i < portalObjs.size(); i++) {
		if (!portalObjs[i]->CanGoIn()) continue;
		coObjects.push_back(portalObjs[i]);
	}

	player->Update(dt, &coObjects);
}

void CPlayOverworldScene::Render()
{
	mapHolder->Render();

	for (int i = 0; i < pathObjs.size(); i++) {
		pathObjs[i]->Render();
	}

	for (int i = 0; i < terrainObjs.size(); i++) {
		terrainObjs[i]->Render();
	}

	for (int i = 0; i < portalObjs.size(); i++) {
		portalObjs[i]->Render();
	}

	for (int i = 0; i < pointObjs.size(); i++) {
		pointObjs[i]->Render();
	}

	player->Render();
	
	if (mainHUD != NULL)
		mainHUD->Render();
}

void CPlayOverworldScene::LoadUI()
{
	CScene::LoadUI();

	float hud_x, hud_y, cam_x, cam_y;

	CGame* game = CGame::GetInstance();
	game->GetCamPos(cam_x, cam_y);
	hud_x = (float)cam_x + game->GetBackBufferWidth() / 2.0f - 16 * 2.5f;
	hud_y = (float)cam_y + game->GetBackBufferHeight() - 16 * 1.75f;

	mainHUD->SetPosition(hud_x, hud_y);
}