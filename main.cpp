#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include "include/playercharacter.h"
#include "include/tools.h"

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
