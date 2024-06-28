#pragma once
#include "UIObject.h"
#include "AssetIDs.h"
#include "NumberUI.h"
#include "IconUI.h"
#include "CharacterIconUI.h"


class CHUD : public CUIObject
{
protected:
	//hud info
	int level;
	int coin;
	int point;
	int life;
	int time;
	int power;

	//card info
	int firstCard;
	int secondCard;
	int thirdCard;

	//icon info
	int characterIconType;

	CNumberUI *levelUI;
	CNumberUI *coinUI;
	CNumberUI* pointUI;
	CNumberUI* lifeUI;
	CNumberUI* timeUI;

	CCharacterIconUI* characterIconUI;

	//power info
	CIconUI* bar_1;
	CIconUI* bar_2;
	CIconUI* bar_3;
	CIconUI* bar_4;
	CIconUI* bar_5;
	CIconUI* bar_6;
	CIconUI* active;


public:
	CHUD(float x, float y);
	virtual void SetPosition(float x, float y);
	virtual void Render();
	void RenderMainHUD();
	void RenderCardHUD();
	void RenderNumberInfoHUD();
	void RenderIconInfoHUD();
	void RenderPowerInfoHUD();

	void SetLevel(int level) { this->level = level; }
	void SetCoin(int coin) { this->coin = coin; }
	void SetPoint(int point) { this->point = point; }
	void SetLife(int life) { this->life = life; }
	void SetTime(int time) { this->time = time; }
	void SetPower(int power) { 
		if (power < 0) power = 0;
		if (power > 6) power = 6;
		this->power = power;
	}
};