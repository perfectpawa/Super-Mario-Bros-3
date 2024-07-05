#include "SaveFile.h"
#include <fstream>
#include <Windows.h>
#include "Game.h"
#include "debug.h"
#include "Utils.h"

SaveFile* SaveFile::__instance = NULL;

SaveFile::SaveFile()
{
}

SaveFile::~SaveFile()
{
}

SaveFile* SaveFile::GetInstance()
{
	if (__instance == NULL) __instance = new SaveFile();
	return __instance;
}

void SaveFile::Save(int save_file_id)
{
	if(save_file_id == -1) save_file_id = this->save_file_id;

	LPCWSTR save_file_path = CGame::GetInstance()->GetSaveFileName(save_file_id);

	// overwrite to file
	ofstream f;
	f.open(save_file_path);


	f << "mario_level\t" << to_string(mario_level) << endl;
	f << "level\t" << to_string(level) << endl;
	f << "score\t" << to_string(score) << endl;
	f << "life\t" << to_string(life) << endl;
	f << "coin\t" << to_string(coin) << endl;
	f << "card_slot_1\t" << to_string(card_slot_1) << endl;
	f << "card_slot_2\t" << to_string(card_slot_2) << endl;
	f << "card_slot_3\t" << to_string(card_slot_3) << endl;
	f << "overworld_x\t" << to_string(overworld_x) << endl;
	f << "overworld_y\t" << to_string(overworld_y) << endl;



	f.close();
}

void SaveFile::Load(int save_file_id)
{
	this->save_file_id = save_file_id;
	LPCWSTR save_file_path = CGame::GetInstance()->GetSaveFileName(save_file_id);

	ifstream f;
	f.open(save_file_path);
	char str[1024];


	while (f.getline(str, 1024))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	
		vector<string> tokens = split(line);

		if (tokens.size() < 2) continue; // skip invalid lines

		if (tokens[0] == "mario_level") {
			mario_level = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "level")
		{
			level = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "score")
		{
			score = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "life")
		{
			life = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "coin")
		{
			coin = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "card_slot_1")
		{
			card_slot_1 = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "card_slot_2")
		{
			card_slot_2 = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "card_slot_3")
		{
			card_slot_3 = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "overworld_x")
		{
			overworld_x = atoi(tokens[1].c_str());
		}
		else if (tokens[0] == "overworld_y")
		{
			overworld_y = atoi(tokens[1].c_str());
		}


	}
	f.close();

	//debug out each value card_slot_1, card_slot_2, card_slot_3
	DebugOut(L"[INFO] card_slot_1: %d\n", card_slot_1);
	DebugOut(L"[INFO] card_slot_2: %d\n", card_slot_2);
	DebugOut(L"[INFO] card_slot_3: %d\n", card_slot_3);

	DebugOut(L"[INFO] Loading save file : %s has been loaded successfully\n", save_file_path);
}

void SaveFile::SetCard(int card)
{
	if (card_slot_1 == 0)
	{
		card_slot_1 = card;
	}
	else if (card_slot_2 == 0)
	{
		card_slot_2 = card;
	}
	else if (card_slot_3 == 0)
	{
		card_slot_3 = card;
	}
}