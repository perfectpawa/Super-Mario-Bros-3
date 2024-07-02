#pragma once
#include "Brick.h"
#include "Coin.h"


#define TYPE_HAVE_COIN		0
#define TYPE_HAVE_BUTTON	1


class CBrickCoin : public CBrick
{
protected:
	int type;
	bool hited = false;
	bool isHide = false;
	CCoin* coin = NULL;
public:
	CBrickCoin(float x, float y, int type);
	virtual void Render();
	virtual int IsBlocking() { return !isHide; }
	virtual void Breaking();
	void SetHide(bool hide) { isHide = hide; }
	void SetCoin(CCoin* coin) { this->coin = coin; }
	CCoin* GetCoin() { return coin; }
	int GetType() { return type; }
};