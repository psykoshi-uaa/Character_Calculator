#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include <string>
#include "include/playercharacter.h"
#include "include/lib.h"
#include "include/cwin.h"

void StateMachine(TalentTree tt, Cwin& cwin, PlayerCharacter& player, AppState& curstate, int& statselected, char& userInp);
void InitTalents(TalentTree& tt);

void initialize(){
	initscr(); cbreak(); noecho();
	keypad(stdscr, TRUE);
}

int deinitialize(){
	endwin();
	return 0;
}

int main(){
	initialize();
	enum AppState curstate = STATE_STATS;
	int statselected = 0;
	char userInp = '\0';
	TalentTree tt;
	Cwin cwin(40, 81, 1, 1);

	while( curstate != STATE_EXIT ){
		clear();
		struct Pos player_origin = { 4, 4 };
		PlayerCharacter player; 
		player.SetPos(player_origin);
		curstate = STATE_STATS;
		
		while( true ){
			StateMachine(tt, cwin, player, curstate, statselected, userInp);
			if( (curstate == STATE_RESET) || (curstate == STATE_EXIT) )
				break;
		}
		if( curstate == STATE_EXIT )
			break;
	}
	return deinitialize();
}

void StateMachine(TalentTree tt, Cwin& cwin, PlayerCharacter& player, AppState& curstate, int& statselected, char& userInp){
	switch( curstate ){
	case STATE_STATS:
		cwin.Print();
		//player.IncreaseStat(int(userInp) - int('0') - 1);
		player.PrintCurrentLevel();
		PrintLevelupPrompt(20, 3);
		userInp = GetUserInp(10, '1', '2', '3', '4', '5', '6', 'q', 'L', 'R', 't');
		if( userInp == 'q' )
			curstate = STATE_EXIT;
		else if( userInp == 'R' )
			curstate = STATE_RESET;
		else if( userInp == 'L' )
			player.Levelup();
		else if( userInp == 't' ){
			clear();
			refresh();
			curstate = STATE_TALENTS;
		}
		break;

	case STATE_TALENTS:
		player.PrintCurrentLevel();
		userInp = GetUserInp(3, 'h', 'l', 'b');
		if( userInp == 'b' )
			curstate = STATE_STATS;
		else if( userInp == 'h' ){
			if( statselected == 0 )
				statselected = NUM_STATS - 1;
			else
				statselected--;
		} else if( userInp == 'l' ){
			if( statselected == NUM_STATS - 1 )
				statselected = 0;
			else
				statselected++;
		}
		break;

	default:
		break;
	}
}

void PrintLevelupPrompt(int y, int x){
	int xx = x;
	mvprintw(y, x, "Select a stat that you would like to upgrade [1-6]");
	for( int i=0; i<NUM_STATS; i++ ){
		mvprintw(y+1, xx, "%i = %s", i + 1, STAT_NAMES[i].c_str());
		xx += 9;
	}
	mvprintw(y + 3, x, "press 'r' to reset and 'q' to quit");
}

void InitTalents(TalentTree& tt){
	tt.AddTalent(0, "Puglism", "Unarmed damage.");
	tt.AddTalent(0, "Headhunter", "Throwing damage.");
	tt.AddTalent(0, "Warrior", "Weapon damage.");
	tt.AddTalent(0, "Mule", "Carry weight.");
	tt.AddTalent(0, "Way of the Frog", "Jumping increase.");
	tt.AddTalent(0, "Way of the Ram", "Knockback increase.");
	tt.AddTalent(0, "Nutcracker", "Grip strength.");
	tt.AddTalent(1, "Mist", "Chance to dodge.");
	tt.AddTalent(1, "Exploiter", "Chance for subcrit.");
	tt.AddTalent(1, "Accuracy M.", "Chance to Hit (Melee weapons).");
	tt.AddTalent(1, "Accuracy R.", "Chance to Hit (Ranged weapons).");
	tt.AddTalent(1, "Accuracy T.", "Chance to Hit (Thrown weapons).");
	tt.AddTalent(1, "Speedster", "Movement speed increase.");
	tt.AddTalent(1, "Sealegs", "Chance to maintain balance.");
	tt.AddTalent(1, "Featherfall", "Reduced fall damage.");
	tt.AddTalent(1, "Ballistics", "Increase projectile range.");
	tt.AddTalent(1, "Avoidance", "Increased saving throw on AoE effects.");
	tt.AddTalent(2, "Hearty", "Health increase.");
	tt.AddTalent(2, "Healthy", "Resistance increase (Bleeding, Poison, Disease).");
	tt.AddTalent(2, "Aegis", "Chance to deflect damage type.");
	tt.AddTalent(2, "Mouth Breather", "Reduced DoT from neck Constriction.");
	tt.AddTalent(2, "Drunkard", "Drinking tolerance.");
	tt.AddTalent(2, "Poise", "Resistance to knockback.");
	tt.AddTalent(2, "Castle", "Make yourself cover for allies.");
	tt.AddTalent(3, "Empty Mind", "Buff duration increase.");
	tt.AddTalent(3, "Magician", "All spell damage increase.");
	tt.AddTalent(3, "Accuracy S.", "Chance to Hit (Spells).");
	tt.AddTalent(3, "Firebender", "Fire and Lightning damage increase.");
	tt.AddTalent(3, "Ice Maiden", "Ice damage increase.");
	tt.AddTalent(3, "Necromancer", "Necrotic damage increase.");
	tt.AddTalent(3, "The Faithful", "Radiant damage increase.");
	tt.AddTalent(3, "Melting Man", "Acid damage increase.");
	tt.AddTalent(4, "Strong Mind", "Increase DC spell break saves.");
	tt.AddTalent(4, "Watch Your Step!", "Chance to spot traps passively.");
	tt.AddTalent(4, "Show Yourself!", "Chance to spot hidden movements passively.");
	tt.AddTalent(4, "The Doctor", "Increase spell healing.");
	tt.AddTalent(4, "Druidic", "Increased offensive nature damage.");
	tt.AddTalent(4, "Magic Mirror", "Chance to deflect small magic projectiles.");
	tt.AddTalent(4, "Writer's Block", "Chance to gain insight while crafting.");
	tt.AddTalent(5, "Knock Knock,", "Chance to be funny.");
	tt.AddTalent(5, "Who's There?", "Chance to persuade door.");
	tt.AddTalent(5, "Charge!", "Chance for nearby allies to roll +1 initiative.");
	tt.AddTalent(5, "Attack!", "Chance for nearby allies to increase primary damage stat +1.");
	tt.AddTalent(5, "Hold the Line!", "Chance for nearby allies to increase AC +1.");
	tt.AddTalent(5, "Presence", "Increased threat.");
	tt.AddTalent(5, "Distract", "Chance to decrease threat for one turn.");
	tt.AddTalent(5, "Bully", "psychic damage increase.");
	tt.AddTalent(6, "Luck", "Lucky.");
}
