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
	int world;
	int coin;
	int score;
	int life;
	int time;
	int power;

	//card info
	int firstCard;
	int secondCard;
	int thirdCard;

	//icon info
	int characterIconType;

	CNumberUI * worldUI;
	CNumberUI *coinUI;
	CNumberUI* scoreUI;
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

	void SetWorld(int world);
	void SetCoin(int coin);
	void SetScore(int score);
	void SetLife(int life);
	void SetTime(int time);

	void SetFirstCard(int firstCard);
	void SetSecondCard(int secondCard);
	void SetThirdCard(int thirdCard);

	void SetPower(int power) { 
		if (power < 0) power = 0;
		if (power > 6) power = 6;
		this->power = power;
	}
};