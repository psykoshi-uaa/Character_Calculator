#pragma once
#include <string>
#include "pos.h"

#define NUM_STATS 7
#define NUM_TALENTS 48
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8
#define NUM_LCK_TALENTS 1

#define SIZE_TALENT_MENU_H 16
#define SIZE_TALENT_MENU_W 24
#define SIZE_SIZE_MENU_H 9
#define SIZE_SIZE_MENU_W 9
#define STAT_MARGIN_Y 4

extern const int NUM_TALENTS_IN_STAT[NUM_STATS];
extern const std::string STAT_NAMES[NUM_STATS];
extern const std::string STAT_NAMES_LONG[NUM_STATS];

int rand_num(int min, int max);
char GetUserInp(int argn, ...);
void PrintLevelupPrompt(int y, int x);

enum AppState { STATE_STATS, STATE_TALENTS, STATE_RESET, STATE_EXIT };
enum StatState { STATE_STR, STATE_DEX, STATE_CON, STATE_INT, STATE_WIS, STATE_CHA, STATE_LCK };

class Talent {
private:
	int level;
	std::string name;
	std::string desc;
	Talent* next;
public:
	Talent();
	Talent(int s, std::string n, std::string d);
	~Talent();
	Talent* GetNext();
	int GetLevel();
	void SetNext(Talent* new_next);
	std::string GetName();
	std::string GetDesc();
};

class TalentTree {
private:
	Talent* head[NUM_STATS];
public:
	TalentTree();
	~TalentTree();
	void AddTalent(int stat, std::string name, std::string desc);
	int GetTalentLevel(int s, int n);
	std::string GetTalentName(int s, int n);
	std::string GetTalentDesc(int s, int n);
};
