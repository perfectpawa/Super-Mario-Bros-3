#include "SaveFile.h"
#include <fstream>
#include <Windows.h>
#include "Game.h"
#include "debug.h"
#include "Utils.h"

SaveFile* SaveFile::__instance = NULL;

SaveFile::SaveFile()
{	
	this->save_file_id = -1;

	this->mario_level = 1;
	this->life = 4;
	this->score = 0;
	this->coin = 0;

	this->card_slot_1 = 0;
	this->card_slot_2 = 0;
	this->card_slot_3 = 0;

	this->world = 1;
	this->save_point_x = 0;
	this->save_point_y = 0;
	this->last_stand_x = 0;
	this->last_stand_y = 0;
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

	ofstream f;
	f.open(save_file_path);
	f << "[PLAYER]" << endl;
	f << "mario_level\t" << to_string(mario_level) << endl;
	f << "life\t" << to_string(life) << endl;
	f << "coin\t" << to_string(coin) << endl;
	f << "score\t" << to_string(score) << endl;

	f << "[CARD]" << endl;
	f << to_string(card_slot_1) << "\t" << to_string(card_slot_2) << "\t" << to_string(card_slot_3) << endl;

	f << "[OVERWORLD]" << endl;
	f << "world\t" << to_string(world) << endl;
	f << "save_point\t" << to_string(save_point_x) << "\t" << to_string(save_point_y) << endl;
	f << "last_stand\t" << to_string(last_stand_x) << "\t" << to_string(last_stand_y) << endl;

	f << "[SUBWORLDHAVECOMPLETE]" << endl;
	for (int i = 0; i < subWorldHasComplete.size(); i++)
	{
		f << to_string(subWorldHasComplete[i]) << "\t";
	}


	f.close();
}

void SaveFile::LoadPlayer(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;

	if (tokens[0] == "mario_level")
	{
		this->mario_level = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "life")
	{
		this->life = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "coin")
	{
		this->coin = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "score")
	{
		this->score = atoi(tokens[1].c_str());
	}
}

void SaveFile::LoadCard(string line)
{
	vector<string> tokens = split(line);

	card_slot_1 = atoi(tokens[0].c_str());
	card_slot_2 = atoi(tokens[1].c_str());
	card_slot_3 = atoi(tokens[2].c_str());
}

void SaveFile::LoadWorld(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;

	if (tokens[0] == "world")
	{
		this->world = atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "save_point")
	{
		this->save_point_x = (float)atof(tokens[1].c_str());
		this->save_point_y = (float)atof(tokens[2].c_str());
	}
	else if (tokens[0] == "last_stand")
	{
		this->last_stand_x = (float)atof(tokens[1].c_str());
		this->last_stand_y = (float)atof(tokens[2].c_str());
	}
}

void SaveFile::LoadSubWorldHasComplete(string line)
{
	vector<string> tokens = split(line);
	for (int i = 0; i < tokens.size(); i++)
	{
		subWorldHasComplete.push_back(atoi(tokens[i].c_str()));
	}
}

void SaveFile::Load(int save_file_id)
{
	this->save_file_id = save_file_id;
	LPCWSTR save_file_path = CGame::GetInstance()->GetSaveFileName(save_file_id);

	ifstream f;
	f.open(save_file_path);
	char str[1024];

	int section = SECTION_UNKNOWN;

	while (f.getline(str, 1024))
	{
		string line(str);

		if(line == "") continue;

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[PLAYER]") { section = SECTION_PLAYER; continue; };
		if (line == "[CARD]") { section = SECTION_CARD; continue; };
		if (line == "[OVERWORLD]") { section = SECTION_OVERWORLD; continue; };
		if (line == "[SUBWORLDHAVECOMPLETE]") { section = SECTION_SUBWORLDHAVECOMPLETE; continue; };
		if (line[0] == '[') { section = SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SECTION_PLAYER: LoadPlayer(line); break;
		case SECTION_CARD: LoadCard(line); break;
		case SECTION_OVERWORLD: LoadWorld(line); break;
		case SECTION_SUBWORLDHAVECOMPLETE: LoadSubWorldHasComplete(line); break;
		}
	}
	f.close();

	//debug out last stand and save point
	DebugOut(L"[INFO] Last stand : %f %f\n", last_stand_x, last_stand_y);
	DebugOut(L"[INFO] Save point : %f %f\n", save_point_x, save_point_y);

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