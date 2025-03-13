#include <curses.h>
#include <random>
#include "../include/lib.h"

std::random_device rd;
std::mt19937 RNGine(rd());
int rand_num(int min, int max){
	std::uniform_int_distribution<int> rand(min, max);
	return rand(RNGine);
}

void PrintLevelupPrompt(int y, int x){
	int xx = x;
	mvprintw(y, x, "Select a stat that you would like to upgrade [1-6]");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvprintw(y+1, xx, "%i = %s", i + 1, STAT_NAMES[i]);
		xx += 9;
	}
	mvprintw(y + 3, x, "press 'r' to reset and 'q' to quit");
}

char GetUserInp(int argn, ...){
	char user_inp;
	while(true) {
		user_inp = getch();
		va_list args;
		va_start(args, argn);
		for( int i=0; i<argn; i++ ){
			if( user_inp == va_arg(args, int) ){
				clear();
				va_end(args);
				return user_inp;
			}
		}
		mvprintw(rand_num(1, 40), rand_num(1, 80), "bad input, try again");
	}
}

const int NUM_TALENTS[] = {NUM_STR_TALENTS, NUM_DEX_TALENTS, NUM_CON_TALENTS, NUM_INT_TALENTS, NUM_WIS_TALENTS, NUM_CHA_TALENTS};

const char* STAT_NAMES[] = {
	"STR",
	"DEX",
	"CON",
	"INT",
	"WIS",
	"CHA"
};

const char* TALENT_NAMES[] = {
//STR
	"pugilism",
	"headhunter",
	"warrior",
	"mule",
	"way of frog",
	"way of ram",
	"nutcracker",
//DEX
	"mist",
	"exploiter",
	"accuracy m.",
	"accuracy r.",
	"accuracy t.",
	"speedster",
	"sealegs",
	"featherfall",
	"ballistics",
	"avoidance",
//CON
	"hearty",
	"healthy",
	"aegis",
	"mouth breather",
	"drunkard",
	"poise",
	"castle",
//INT
	"empty mind",
	"magician",
	"accuracy s.",
	"firebender",
	"ice maiden",
	"necromancer",
	"the faithful",
	"melting man",
//WIS
	"strong mind",
	"watch your step",
	"show yourself!",
	"the doctor",
	"druidic",
	"magic mirroe",
	"writer's block",
//CHA
	"knock knock,",
	"who's there?",
	"charge!",
	"attack!",
	"hold the line!",
	"presence",
	"distract",
	"bully"
};


