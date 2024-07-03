#pragma once

class SaveFile {
	static SaveFile* __instance;
	int save_file_id;
	int level;
	int score;
	int life;
	int coin;
	int card_slot_1;
	int card_slot_2;
	int card_slot_3;
public:
	SaveFile();
	~SaveFile();
	static SaveFile* GetInstance();
	void Save(int save_file_id);
	void Load(int save_file_id);

	void SetLevel(int level) { this->level = level; }
	int GetLevel() { return level; }

	void SetScore(int score) { this->score = score; }
	int GetScore() { return score; }

	void SetLife(int life) { this->life = life; }
	int GetLife() { return life; }

	void SetCoin(int coin) { this->coin = coin; }
	void AddCoin(int coin) { this->coin += coin; }
	int GetCoin() { return coin; }

	void SetCardSlot1(int card_slot_1) { this->card_slot_1 = card_slot_1; }
	int GetCardSlot1() { return card_slot_1; }

	void SetCardSlot2(int card_slot_2) { this->card_slot_2 = card_slot_2; }
	int GetCardSlot2() { return card_slot_2; }

};

typedef SaveFile* LPSAVEFILE;