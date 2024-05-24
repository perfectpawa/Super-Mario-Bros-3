#include "SpawnCheck.h"

void CSpawnCheck::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SPAWN_CHECK_BBOX_WIDTH / 2;
	top = y - SPAWN_CHECK_BBOX_HEIGHT / 2;
	right = left + SPAWN_CHECK_BBOX_WIDTH;
	bottom = top + SPAWN_CHECK_BBOX_HEIGHT;
}

void CSpawnCheck::Render()
{
	RenderBoundingBox();
}
