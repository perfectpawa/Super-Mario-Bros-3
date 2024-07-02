#include "BrickCoin.h"
#include "Animations.h"
#include "Button.h"

CBrickCoin::CBrickCoin(float x, float y, int type) : CBrick(x, y, 0)
{
	this->type = type;
}

void CBrickCoin::Render()
{
	if(!hited) CAnimations::GetInstance()->Get(ID_ANI_BRICK_BREAKABLE)->Render(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_BRICK_BREAKABLE_HIT)->Render(x, y); 
}

void CBrickCoin::Breaking()
{
	if (type != TYPE_HAVE_BUTTON) {
		this->Delete();
		return;
	}
	if(hited) return;
	hited = true;
	
	CButton* button = new CButton(x, y - 16);
	CGame::GetInstance()->GetCurrentScene()->AddObject(button, OBJECT_TYPE_BUTTON);
}