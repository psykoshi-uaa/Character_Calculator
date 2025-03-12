#pragma once
#define NUM_OF_STATS 6
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8

extern const char* STAT_NAMES[6];

int rand_num(int min, int max);
char get_user_inp();

struct Vector {
	int y;
	int x;
};
