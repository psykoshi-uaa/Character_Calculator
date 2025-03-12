#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>

#define NUM_OF_STATS 6
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8

void print_levelup_prompt(int y, int x);
int initialize();
int deinitialize();
int rand_num(int min, int max);
char get_user_inp();

struct Vector {
	int y;
	int x;
};

std::random_device rd;
std::mt19937 RNGine(rd());

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

public:
	PlayerCharacter();
	~PlayerCharacter();
	void levelup();
	void generate_talent_points();
	void IncreaseStat(int stat);
	void print_current_level();
	void print_stats();
	void print_talent_points();
	void print_talents(int y, int x);
};

//						MAIN
int main(){
	int exit_code = initialize();
	char user_inp;

	while( user_inp != 'q' ){
		clear();
		refresh();

		PlayerCharacter player;

		while( true ){
			clear();
			refresh();

			player.IncreaseStat(int(user_inp) - int('0') - 1);

			if( user_inp == 'l' ){
				player.levelup();
			}

			player.print_current_level();
			player.print_stats();
			player.print_talent_points();
			print_levelup_prompt(20, 1);
			player.print_talents(28, 1);

			user_inp = get_user_inp();
			if( user_inp == 'q' || user_inp == 'r' )
				break;
		}
	}

	return deinitialize();
}

//						FUNCTIONS
int rand_num(int min, int max){
	std::uniform_int_distribution<int> rand(min, max);
	return rand(RNGine);
}

int initialize(){
	initscr(); cbreak(); noecho();
	keypad(stdscr, TRUE);
	return 0;
}

int deinitialize(){
	endwin();
	return 0;
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
		'1', '2', '3', '4', '5', '6', 'q', 'l', 'r'
	};
	while(true) {
		user_inp = getch();
		for( int i=0; i<sizeof(valid_inp); i++ ){
			if( user_inp == valid_inp[i] ){
				return user_inp;
			}
		}
		mvprintw(rand_num(1, 40), rand_num(1, 80), "bad input, try again");
	}
}

//						PLAYER CLASS
PlayerCharacter::PlayerCharacter()
: level(0) {
	pos = {1, 1};
	for( int i=0; i<NUM_OF_STATS; i++ ){
		stats[i] = 6;
		talent_points[i] = 0;
	}
	for( int i=0; i<NUM_STR_TALENTS; i++ )
		str_talents[i] = 0;
	for( int i=0; i<NUM_DEX_TALENTS; i++ )
		dex_talents[i] = 0;
	for( int i=0; i<NUM_CON_TALENTS; i++ )
		con_talents[i] = 0;
	for( int i=0; i<NUM_INT_TALENTS; i++ )
		int_talents[i] = 0;
	for( int i=0; i<NUM_WIS_TALENTS; i++ )
		wis_talents[i] = 0;
	for( int i=0; i<NUM_CHA_TALENTS; i++ )
		cha_talents[i] = 0;
}

PlayerCharacter::~PlayerCharacter(){
}

void PlayerCharacter::levelup(){
	generate_talent_points();
	level += 1;
}

void PlayerCharacter::generate_talent_points(){
	for( int i=0; i<NUM_OF_STATS; i++ ){
		int dice_thrown = 0;
		if( stats[i] > 18 ){
			dice_thrown = 6;
		} else if( stats[i] > 16 ){
			dice_thrown = 5;
		} else if( stats[i] > 14 ){
			dice_thrown = 4;
		} else if( stats[i] > 12 ){
			dice_thrown = 3;
		} else if( stats[i] > 10 ){
			dice_thrown = 2;
		} else if( stats[i] > 7 ){
			dice_thrown = 1;
		}

		for( int j=0; j<dice_thrown; j++ ){
			talent_points[i] += rand_num(1, 4);
		}
	}
}

void PlayerCharacter::IncreaseStat(int stat){
	stats[stat] += 1;
}

void PlayerCharacter::print_current_level(){
	mvprintw(pos.y, pos.x + 4, "LEVEL: %i", level);
}

void PlayerCharacter::print_stats(){
	struct Vector temp_pos = {pos.y + 2, pos.x};
	mvaddstr(temp_pos.y, temp_pos.x, "stats:");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvaddstr(temp_pos.y + 1 + i, temp_pos.x, STAT_NAMES[i]);
		mvprintw(temp_pos.y + 1 + i, temp_pos.x + 5, "%i", stats[i]);
	}
}

void PlayerCharacter::print_talent_points(){
	struct Vector temp_pos = {pos.y + 10, pos.x};
	mvaddstr(temp_pos.y, temp_pos.x, "talent points:");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvaddstr(temp_pos.y + 1 + i, temp_pos.x, STAT_NAMES[i]);
		mvprintw(temp_pos.y + 1 + i, temp_pos.x + 5, "%i", talent_points[i]);
	}
}

void PlayerCharacter::print_talents(int y, int x){
	Vector offset = { 0 };
	int margin = 25;
	for( int i=0; i<NUM_STR_TALENTS; i++ )
		mvprintw(y + i, offset.x, "[+%i] %s", str_talents[i], STR_TALENT_NAMES[i]);
	offset.x += margin;
	for( int i=0; i<NUM_DEX_TALENTS; i++ )
		mvprintw(y + i + offset.y, offset.x, "[+%i] %s", dex_talents[i], DEX_TALENT_NAMES[i]);
	offset.x += margin;
	for( int i=0; i<NUM_CON_TALENTS; i++ )
		mvprintw(y + i + offset.y, offset.x, "[+%i] %s", con_talents[i], CON_TALENT_NAMES[i]);
	offset.x += margin;
	for( int i=0; i<NUM_INT_TALENTS; i++ )
		mvprintw(y + i + offset.y, offset.x, "[+%i] %s", int_talents[i], INT_TALENT_NAMES[i]);
	offset.x += margin;
	for( int i=0; i<NUM_WIS_TALENTS; i++ )
		mvprintw(y + i + offset.y, offset.x, "[+%i] %s", wis_talents[i], WIS_TALENT_NAMES[i]);
	offset.x += margin;
	for( int i=0; i<NUM_CHA_TALENTS; i++ )
		mvprintw(y + i + offset.y, offset.x, "[+%i] %s", cha_talents[i], CHA_TALENT_NAMES[i]);
}
