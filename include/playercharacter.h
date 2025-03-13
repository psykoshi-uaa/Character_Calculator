#pragma once
#include <curses.h>
#include "tools.h"
#include "cwind.h"

extern const char* STAT_NAMES[6];
extern const char* STR_TALENT_NAMES[NUM_STR_TALENTS];
extern const char* DEX_TALENT_NAMES[NUM_DEX_TALENTS];
extern const char* CON_TALENT_NAMES[NUM_CON_TALENTS];
extern const char* INT_TALENT_NAMES[NUM_INT_TALENTS];
extern const char* WIS_TALENT_NAMES[NUM_WIS_TALENTS];
extern const char* CHA_TALENT_NAMES[NUM_CHA_TALENTS];

class PlayerCharacter {
private:
	struct Vector pos;
	int stats[NUM_OF_STATS];
	int talent_points[NUM_OF_STATS];
	int level;
	int str_talents[NUM_STR_TALENTS];
	int dex_talents[NUM_DEX_TALENTS];
	int con_talents[NUM_CON_TALENTS];
	int int_talents[NUM_INT_TALENTS];
	int wis_talents[NUM_WIS_TALENTS];
	int cha_talents[NUM_CHA_TALENTS];
	Cwind* talent_wind[NUM_OF_STATS];
	void SetTalentWind();

public:
	PlayerCharacter();
	~PlayerCharacter();
	void Levelup();
	void GenerateTalentPoints();
	void IncreaseStat(int stat);
	void SetPosition(int y, int x);
	void PrintCurrentLevel();
	void PrintStats();
	void PrintTalentPoints();
	void PrintTalents();
};
