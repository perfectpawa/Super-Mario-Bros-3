#include "LevelKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CLevelKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_1: {
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	}
	case DIK_2: {
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	}
	case DIK_3: {
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	}
	case DIK_0: {
		mario->SetState(MARIO_STATE_DIE);
		break;
	}
	case DIK_R: {
		CGame::GetInstance()->ReloadScene();
		break;
	}
	case DIK_DOWN: {
		mario->SetState(MARIO_STATE_SIT);
		break;
	}
	case DIK_S: {
		mario->SetWantJump(true);
		mario->SetWantFloat(true);
		break;
	}
	case DIK_D: {
		mario->SetWantPickUp(true);
		break;
	}
	case DIK_A: {
		mario->SetWantWhip(true);
		mario->StartGearing();
		break;
	}
	case DIK_RIGHT: {
		mario->SetMovingRight(true);
		break;
	}
	case DIK_LEFT: {
		mario->SetMovingLeft(true);
		break;
	}
	}
}

void CLevelKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S: {
		mario->SetWantReleaseJump(true);
		break;
	}
	case DIK_DOWN: {
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
	case DIK_D: {
		mario->SetWantPickUp(false);
		mario->SetState(MARIO_STATE_KICK);
		break;
	}
	case DIK_A: {	
		mario->EndGearing();
		break;
	}
	case DIK_RIGHT: {
		mario->SetMovingRight(false);
		break;
	}
	case DIK_LEFT: {
		mario->SetMovingLeft(false);
		break;
	}
	}
}

void CLevelKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}