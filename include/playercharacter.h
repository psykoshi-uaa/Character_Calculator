#pragma once
#include <curses.h>
#include <string>
#include "lib.h"
#include "cwin.h"
#include "pos.h"

extern const std::string STAT_NAMES[NUM_STATS];
extern const std::string TALENT_NAMES[NUM_TALENTS];

class PlayerCharacter {
private:
	struct Pos pos;
	int stats[NUM_STATS];
	int talent_points[NUM_STATS];
	int talents_pointed[NUM_STATS][NUM_TALENTS];
	int level;
	Cwin* stat_win[NUM_STATS];
	Cwin* talent_win[NUM_STATS];

public:
	PlayerCharacter();
	~PlayerCharacter();
	void Levelup();
	void GenerateTalentPoints();
	void IncreaseStat(int stat);
	void SetPos(struct Pos new_pos);
	void PrintCurrentLevel();
};
