#pragma once

#include "Scene.h"

class COverworldKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	COverworldKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
