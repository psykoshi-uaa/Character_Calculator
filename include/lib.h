#pragma once
#define NUM_OF_STATS 6
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8
#define TOTAL_TALENTS 47

#define SIZE_TALENT_MENU_H 16
#define SIZE_TALENT_MENU_W 24

extern const int NUM_TALENTS[NUM_OF_STATS];
extern const char* STAT_NAMES[NUM_OF_STATS];

int rand_num(int min, int max);
char GetUserInp(int argn, ...);
void PrintLevelupPrompt(int y, int x);

enum CurState { STATE_STATS, STATE_TALENTS, STATE_RESET, STATE_EXIT };

struct Vector {
	int y;
	int x;
};
