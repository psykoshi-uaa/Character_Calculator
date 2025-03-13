#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include "include/playercharacter.h"
#include "include/tools.h"
#include "include/cwind.h"

void print_levelup_prompt(int y, int x);

int initialize(){
	initscr(); cbreak(); noecho();
	keypad(stdscr, TRUE);
	return 0;
}

int deinitialize(){
	endwin();
	return 0;
}

int main(){
	int exit_code = initialize();
	char user_inp;

	while( user_inp != 'q' ){
		clear();
		PlayerCharacter player;
		
		while( true ){
			player.IncreaseStat(int(user_inp) - int('0') - 1);

			if( user_inp == 'l' ){
				player.Levelup();
			} else if( user_inp == 't' ){
				clear();
				refresh();
				while( true ){
					player.PrintTalents();
					user_inp = get_user_inp();
				}
			}

			player.PrintCurrentLevel();
			player.PrintStats();
			player.PrintTalentPoints();
			print_levelup_prompt(20, 1);

			user_inp = get_user_inp();
			if( user_inp == 'q' || user_inp == 'r' )
				break;
		}
	}
	return deinitialize();
}
