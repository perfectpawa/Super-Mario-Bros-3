#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
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
		mario->SetState(MARIO_STATE_JUMP);
		break;
	}
	case DIK_D: {
		mario->SetWantPickUp(true);
		break;
	}
	case DIK_A: {
		mario->SetCanWhip(true);
		mario->StartSprinting();
		break;
	}
	case DIK_RIGHT: {
		mario->SetMovingRight(true);
		mario->SetLookingRight(true);
		mario->ResetSprint();
		break;
	}
	case DIK_LEFT: {
		mario->SetMovingLeft(true);
		mario->SetLookingRight(false);
		mario->ResetSprint();
		break;
	}
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S: {
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
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
		mario->StopSprinting();
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

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	/*int state, level;
	bool canWhip;
	mario->GetState(state);
	mario->GetLevel(level);
	mario->GetCanWhip(canWhip);

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);

	if (game->IsKeyDown(DIK_A) && level == MARIO_LEVEL_RACOON && canWhip) {
		mario->SetState(MARIO_STATE_WHIP);
	}*/

}