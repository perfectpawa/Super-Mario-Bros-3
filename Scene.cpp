#include "Scene.h"
#include "SaveFile.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
	this->key_handler = NULL;
	this->mainHUD = NULL;
}

void CScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	if (tokens[0] == "time") {
		if (timeLimit == -1) timeLimit = (float)atof(tokens[1].c_str());
	}

	if (tokens[0] == "background_color") {
		float r = (float)atof(tokens[1].c_str());
		float g = (float)atof(tokens[2].c_str());
		float b = (float)atof(tokens[3].c_str());

		backgroundColor = D3DXCOLOR(r / 255, g / 255, b / 255, 0.0f);
	}

	if (tokens[0] == "cam_limit") {
		if (tokens.size() > 1) camLimitLeft = (float)atof(tokens[1].c_str());
		if (tokens.size() > 2) camLimitRight = (float)atof(tokens[2].c_str());
		if (tokens.size() > 3) camLimitBottom = (float)atof(tokens[3].c_str());
		if (tokens.size() > 4) camLimitTop = (float)atof(tokens[4].c_str());
		if (tokens.size() > 5) camVerticalFreeZone = (float)atof(tokens[5].c_str());
	}
}

void CScene::FreezeScene(ULONGLONG time)
{
	isFreeze = true;
	freezeTime = time;
	freeze_start = GetTickCount64();
}

void CScene::Update(DWORD dt)
{
	if (isFreeze)
	{
		if (GetTickCount64() - freeze_start > freezeTime)
		{
			isFreeze = false;
			freeze_start = -1;
		}
	}
}

void CScene::LoadUI() {
	DebugOut(L"[INFO] Start loading UI\n");
	mainHUD = new CHUD(0, 0);

	LPSAVEFILE saveFile = SaveFile::GetInstance();

	mainHUD->SetCoin(saveFile->GetCoin());
	mainHUD->SetScore(saveFile->GetScore());
	mainHUD->SetLife(saveFile->GetLife());
	mainHUD->SetLevel(saveFile->GetLevel());

	mainHUD->SetFirstCard(saveFile->GetCardSlot1());
	mainHUD->SetSecondCard(saveFile->GetCardSlot2());
	mainHUD->SetThirdCard(saveFile->GetCardSlot3());
}

void CScene::UpdateUI(DWORD dt) {
	if (mainHUD == NULL) return;
	LPSAVEFILE saveFile = SaveFile::GetInstance();

	mainHUD->SetCoin(saveFile->GetCoin());
	mainHUD->SetScore(saveFile->GetScore());
	mainHUD->SetLife(saveFile->GetLife());
	mainHUD->SetLevel(saveFile->GetLevel());

	mainHUD->SetFirstCard(saveFile->GetCardSlot1());
	mainHUD->SetSecondCard(saveFile->GetCardSlot2());
	mainHUD->SetThirdCard(saveFile->GetCardSlot3());
}
