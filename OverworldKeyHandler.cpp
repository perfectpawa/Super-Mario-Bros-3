#include "OverworldKeyHandler.h"

#include "debug.h"
#include "Game.h"

#include "PlayScene.h"

#include "OW_Mario.h"

void COverworldKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	COWMario* OW_player = (COWMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetOWPlayer();

	switch (KeyCode)
	{
	case DIK_LEFT: {
		OW_player->MoveHorizontal(-1);
		break;
	}
	case DIK_RIGHT: {
		OW_player->MoveHorizontal(1);
		break;
	}
	case DIK_UP: {
		OW_player->MoveVertical(-1);
		break;
	}
	case DIK_DOWN: {
		OW_player->MoveVertical(1);
		break;
	}
	default:
		break;
	}
}

void COverworldKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}

void COverworldKeyHandler::KeyState(BYTE* states)
{

}