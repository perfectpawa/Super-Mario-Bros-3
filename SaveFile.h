#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "Game.h"

#include "debug.h"
#include "Utils.h"

using namespace std;

#define SECTION_UNKNOWN -1
#define SECTION_PLAYER 1
#define SECTION_CARD 2
#define SECTION_OVERWORLD 3
#define SECTION_LEVELHAVECOMPLETE	4

class SaveFile {
	static SaveFile* __instance;
	int save_file_id;

	int mario_level;
	int life;
	int coin;
	int score;

	int card_slot_1;
	int card_slot_2;
	int card_slot_3;

	int world;
	float save_point_x;
	float save_point_y;
	float last_stand_x;
	float last_stand_y;

	vector<int> levelHasComplete;

public:
	SaveFile();
	~SaveFile();
	static SaveFile* GetInstance();
	void Save(int save_file_id = -1);
	void Load(int save_file_id);

	void LoadPlayer(string line);
	void LoadCard(string line);
	void LoadWorld(string line);
	void LoadLevelHasComplete(string line);

	bool isLevelHasComplete(int level) {
		for (int i = 0; i < levelHasComplete.size(); i++) {
			if (levelHasComplete[i] == level) return true;
		}
		return false;
	}

	void SetMarioLevel(int mario_level) { this->mario_level = mario_level; }
	int GetMarioLevel() { return mario_level; }

	void SetWorld(int world) { this->world = world; }
	int GetWorld() { return world; }
	void AddWorld(int world) { this->world += world; }

	void SetScore(int score) { this->score = score; }
	int GetScore() { return score; }
	void AddScore(int score) { this->score += score; }

	void SetLife(int life) { this->life = life; }
	int GetLife() { return life; }
	void AddLife(int life) { this->life += life; }

	void SetCoin(int coin) { this->coin = coin; }
	void AddCoin(int coin) { this->coin += coin; }
	int GetCoin() { return coin; }


	void SetCardSlot1(int card_slot_1) { this->card_slot_1 = card_slot_1; }
	int GetCardSlot1() { return card_slot_1; }

	void SetCardSlot2(int card_slot_2) { this->card_slot_2 = card_slot_2; }
	int GetCardSlot2() { return card_slot_2; }

	void SetCardSlot3(int card_slot_3) { this->card_slot_3 = card_slot_3; }
	int GetCardSlot3() { return card_slot_3; }

	void SetCard(int card);

	void SetSavePoint(float x, float y) { save_point_x = x; save_point_y = y; }
	void GetSavePoint(float& x, float& y) { x = save_point_x; y = save_point_y; }

	void SetLastStand(float x, float y) { last_stand_x = x; last_stand_y = y; }
	void GetLastStand(float& x, float& y) { x = last_stand_x; y = last_stand_y; }

	void AddLevelCompleted(int level_id) { levelHasComplete.push_back(level_id); }

};

typedef SaveFile* LPSAVEFILE;