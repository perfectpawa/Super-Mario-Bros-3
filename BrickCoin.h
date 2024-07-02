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
public:
	CBrickCoin(float x, float y, int type);
	virtual void Render();
	virtual void Breaking();
	int GetType() { return type; }
};