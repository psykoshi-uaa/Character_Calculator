#include <curses.h>
#include <random>
#include "../include/tools.h"

std::random_device rd;
std::mt19937 RNGine(rd());
int rand_num(int min, int max){
	std::uniform_int_distribution<int> rand(min, max);
	return rand(RNGine);
}

void print_levelup_prompt(int y, int x){
	int xx = x;
	mvprintw(y, x, "Select a stat that you would like to upgrade [1-6]");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvprintw(y+1, xx, "%i = %s", i + 1, STAT_NAMES[i]);
		xx += 9;
	}
	mvprintw(y + 3, x, "press 'r' to reset and 'q' to quit");
}

char get_user_inp(){
	char user_inp;
	char valid_inp[] = {
		'1', '2', '3', '4', '5', '6', 'q', 'l', 'r', 't'
	};
	while(true) {
		user_inp = getch();
		for( int i=0; i<sizeof(valid_inp); i++ ){
			if( user_inp == valid_inp[i] ){
				clear();
				return user_inp;
			}
		}
		mvprintw(rand_num(1, 40), rand_num(1, 80), "bad input, try again");
	}
}

const char* STAT_NAMES[] = {
	"STR",
	"DEX",
	"CON",
	"INT",
	"WIS",
	"CHA"
};

const char* STR_TALENT_NAMES[] = {
	"pugilism",
	"headhunter",
	"warrior",
	"mule",
	"way of frog",
	"way of ram",
	"nutcracker"
};

const char* DEX_TALENT_NAMES[] = {
	"mist",
	"exploiter",
	"accuracy m.",
	"accuracy r.",
	"accuracy t.",
	"speedster",
	"sealegs",
	"featherfall",
	"ballistics",
	"avoidance"
};

const char* CON_TALENT_NAMES[] = {
	"hearty",
	"healthy",
	"aegis",
	"mouth breather",
	"drunkard",
	"poise",
	"castle"
};

const char* INT_TALENT_NAMES[] = {
	"empty mind",
	"magician",
	"accuracy s.",
	"firebender",
	"ice maiden",
	"necromancer",
	"the faithful",
	"melting man"
};

const char* WIS_TALENT_NAMES[] = {
	"strong mind",
	"watch your step",
	"show yourself!",
	"the doctor",
	"druidic",
	"magic mirroe",
	"writer's block"
};

const char* CHA_TALENT_NAMES[] = {
	"knock knock,",
	"who's there?",
	"charge!",
	"attack!",
	"hold the line!",
	"presence",
	"distract",
	"bully"
};
