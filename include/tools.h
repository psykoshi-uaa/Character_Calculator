#pragma once
#define NUM_OF_STATS 6
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8

#define SIZE_TALENT_MENU_H 10
#define SIZE_TALENT_MENU_W 15

extern const char* STAT_NAMES[NUM_OF_STATS];

int rand_num(int min, int max);
char get_user_inp();

struct Vector {
	int y;
	int x;
};
