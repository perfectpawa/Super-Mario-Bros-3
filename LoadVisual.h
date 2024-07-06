#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;

//singleton class
class LoadVisual
{
	static LoadVisual* __instance;

public:
	static LoadVisual* GetInstance();
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ASSETS(string line);
	void LoadAssets(LPCWSTR assetFile);
};