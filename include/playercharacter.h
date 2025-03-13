#pragma once
#include <curses.h>
#include "lib.h"
#include "cwind.h"

extern const int NUM_TALENTS[NUM_OF_STATS];
extern const char* STAT_NAMES[NUM_OF_STATS];
extern const char* TALENT_NAMES[TOTAL_TALENTS];

class PlayerCharacter {
private:
	struct Vector pos;
	int stats[NUM_OF_STATS];
	int talent_points[NUM_OF_STATS];
	int talents_pointed[NUM_OF_STATS][TOTAL_TALENTS];
	int level;
	const char* talents[NUM_OF_STATS][10];
	Cwind* stat_wind[NUM_OF_STATS];
	Cwind* talent_wind[NUM_OF_STATS];
	void SetStatWind();
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
	void PrintTalent(int y, int x, int t);
	void PrintTalents();
};
