#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include "include/playercharacter.h"
#include "include/lib.h"
#include "include/cwind.h"

void StateMachine(PlayerCharacter& player, CurState& curstate, char& userInp);

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
	enum CurState curstate = STATE_STATS;
	int exit_code = initialize();
	char userInp = '\0';

	while( curstate != STATE_EXIT ){
		clear();
		PlayerCharacter player;
		curstate = STATE_STATS;
		
		while( true ){
			StateMachine(player, curstate, userInp);
			if( (curstate == STATE_RESET) || (curstate == STATE_EXIT) )
				break;
		}
		if( curstate == STATE_EXIT )
			break;
	}
	return deinitialize();
}

void StateMachine(PlayerCharacter& player, CurState& curstate, char& userInp){
	switch( curstate ){
	case STATE_STATS:
		player.IncreaseStat(int(userInp) - int('0') - 1);
		player.PrintCurrentLevel();
		player.PrintStats();
		PrintLevelupPrompt(20, 1);
		userInp = GetUserInp(10, '1', '2', '3', '4', '5', '6', 'q', 'l', 'R', 't');
		if( userInp == 'q' )
			curstate = STATE_EXIT;
		else if( userInp == 'r' )
			curstate = STATE_RESET;
		else if( userInp == 'l' )
			player.Levelup();
		else if( userInp == 't' ){
			clear();
			refresh();
			curstate = STATE_TALENTS;
		}

		break;
	case STATE_TALENTS:
		player.PrintTalents();
		player.PrintCurrentLevel();
		player.PrintTalentPoints();
		userInp = GetUserInp(2, 'b', 'q');
		if( userInp == 'b' )
			curstate = STATE_STATS;
		break;
	default:
		break;
	}
}
