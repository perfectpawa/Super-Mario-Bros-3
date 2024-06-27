#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "OW_GameObject.h"
#include "Sprites.h"

COWGameObject::COWGameObject()
{
	x = y = 0;
	isDeleted = false;
	canGoIn = false;
}

COWGameObject::~COWGameObject()
{

}