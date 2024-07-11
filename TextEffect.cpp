#include "TextEffect.h"

CTextEffect::CTextEffect(float x, float y, string text, int spriteId, int offset) : CEffectObject(x, y)
{
	this->text = text;
	this->spriteId = spriteId;
	this->offset = offset;
}

void CTextEffect::Update(DWORD dt) {

}

void CTextEffect::Render() {

	int charId = -1;
	for (int i = 0; i < text.size(); i++) {
		//caculate charID, a->1, b->2, ...
		if (text[i] >= 'a' && text[i] <= 'z') {
			charId = text[i] - 'a' + 1;
		}

		if (text[i] == ' ') charId = -1;
		if(charId == -1) continue;

		int spriteId = ID_SPRITE_CHAR_UI_BASE + charId;
		CSprites::GetInstance()->Get(spriteId)->Draw(x + i * 8, y);
	}

	if (spriteId != -1)
		CSprites::GetInstance()->Get(spriteId)->Draw(x + text.size() * 8 + offset, y);

}