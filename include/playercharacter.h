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
	std::string name;
	int level;
	int stat[NUM_STATS];
	int stat_points;
	int potential_stat[NUM_STATS];
	int talent_point[NUM_STATS];
	int potential_talent_point[NUM_STATS];
	Talent* talent;
	Cwin* stat_win[NUM_STATS];
	Cwin* talent_win;

public:
	PlayerCharacter();
	PlayerCharacter(std::string n, TalentTree* t);
	~PlayerCharacter();
	void Levelup();
	void AddPotentialTalentPoint(int* s);
	void RemovePotentialTalentPoint(int* s);
	void ConvertPotentialTalentPoints();
	void GenerateTalentPoints();
	void SetStat(int stat, int n);
	void SetPotentialStats();
	void AddPotentialStat(int i);
	void RemovePotentialStat(int i);
	void ConvertPotentialStats();
	int GetLevel();
	int GetStat(int i);
	int GetStatPoints();
	int GetPotentialStat(int i);
	int GetTalentPoint(int i);
	int GetPotentialTalentPoint(int i);
	int GetTalentLevel(int s, std::string n);
};
