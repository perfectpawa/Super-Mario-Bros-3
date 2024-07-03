#include "SaveFile.h"
#include <fstream>
#include <Windows.h>
#include "Game.h"
#include "debug.h"
#include "Utils.h"

SaveFile* SaveFile::__instance = NULL;

SaveFile::SaveFile()
{
	save_file_id = 0;
	level = 0;
	score = 0;
	life = 0;
	coin = 0;
	card_slot_1 = 0;
	card_slot_2 = 0;
	card_slot_3 = 0;
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
	LPCWSTR save_file_path = CGame::GetInstance()->GetSaveFileName(save_file_id);

	// overwrite to file
	ofstream f;
	f.open(save_file_path);

	f << "# Save file of game" << endl;
	f << "level " << level << endl;
	f << "score " << score << endl;
	f << "life " << life << endl;
	f << "coin " << coin << endl;
	f << "card_slot_1 " << card_slot_1 << endl;
	f << "card_slot_2 " << card_slot_2 << endl;
	f << "card_slot_3 " << card_slot_3 << endl;

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

		
		if (tokens[0] == "level")
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


	}
	f.close();

	DebugOut(L"[INFO] Loading save file : %s has been loaded successfully\n", save_file_path);
}