#pragma once

#include "Scene.h"

class CLevelKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CLevelKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
