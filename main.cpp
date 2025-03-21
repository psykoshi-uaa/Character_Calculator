#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include <string>
#include "include/playercharacter.h"
#include "include/lib.h"
#include "include/cwin.h"
#include "include/prints.h"

void StateMachine(TalentTree* tt, Cwin* cwin[3], PlayerCharacter& player, AppState& curstate, int* selector, char& userInp, struct Pos tooltip_pos);
void IncrementInt(int& i, int m);
void DecrementInt(int& i, int m);
void IncrementIntLoop(int& i, int m);
void DecrementIntLoop(int& i, int m);
TalentTree* InitTalents();

void initialize(){
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
}

int deinitialize(){
	endwin();
	return 0;
}

int main(){
	initialize();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_BLACK, COLOR_CYAN);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);

	enum AppState curstate = STATE_STATS;
	int selector[3] = { 0 };
	selector[2] = { -1 };
	char userInp = '\0';
	TalentTree* tt = InitTalents();

	struct Pos screensize = { 0 };
	getmaxyx(stdscr, screensize.y, screensize.x);
	screensize = {screensize.y-2, screensize.x-2};
	Cwin* cwin[3];
	cwin[0] = new Cwin(screensize.y/2, screensize.x/2, 1, 1);
	cwin[1] = new Cwin(4, 6, 7, 5);
	cwin[2] = new Cwin(30, 5, 20, 3);
	struct Pos tooltip_pos = { screensize.y/2+3, 3};

	while( curstate != STATE_EXIT ){
		clear();
		PlayerCharacter player("Test McTestington", tt); 
		curstate = STATE_STATS;
		
		while( true ){
			StateMachine(tt, cwin, player, curstate, selector, userInp, tooltip_pos);
			if( (curstate == STATE_RESET) || (curstate == STATE_EXIT) )
				break;
		}
		if( curstate == STATE_EXIT )
			break;
	}
	return deinitialize();
}

void StateMachine(TalentTree* tt, Cwin* cwin[3], PlayerCharacter& player, AppState& curstate, int* selector, char& userInp, struct Pos tooltip_pos){
	struct Pos levelpos = { 1, 3 };
	struct Pos statpos = { 3, 7 };
	struct Pos talentpos = { 4, 27 };
	struct Pos descpos = { 4, 55 };
	int num_talents_in_stat = NUM_TALENTS_IN_STAT[selector[0]] - 1;
	int temp_sp = player.GetStatPoints();
	cwin[0]->Print();

//i1.0
	switch( curstate ){
	case STATE_STATS:
		PrintCurrentLevel(player, levelpos);
		PrintCurrentStats(cwin[1], player, statpos, -1);
		PrintStatNames(statpos, selector, STAT_MARGIN_Y);
		PrintAvailableTalentPoints(player, {statpos.y+2, statpos.x+7});
		PrintStatTalents(tt, player, talentpos, selector);
		PrintTalentSpent(player, talentpos, selector);
		PrintHelp(tooltip_pos, 0);
		if( selector[1] == 1 )
			PrintStatTalentsDesc(tt, descpos, selector);
		else
			PrintStatDescription(descpos, selector[0]);

		userInp = GetUserInp(11, 'h', 'j', 'k', 'l', 'q', 'H', 'L', 'U', 'R', 'B');
		if( userInp == 'q' ){
			curstate = STATE_EXIT;
		} else if( userInp == 'l'){
			if( selector[1] == 0 ){
				selector[2] = 0;
			}
			selector[1] = 1;
			IncrementInt(selector[1], 1);
		} else if( userInp == 'h'){
			if( selector[1] == 1 ){
				selector[2] = -1;
			}
			DecrementInt(selector[1], 0);

		} else if( userInp == 'R' ){
			curstate = STATE_RESET;
		} else if( userInp == 'U' ){
			selector[0] = 0;
			selector[1] = 0;
			player.SetPotentialTalentPoints();
			curstate = STATE_LEVELUP;
		} else if( userInp == 'B' ){
			selector[0] = 0;
			selector[1] = 0;
			player.SetPotentialStats();
			curstate = STATE_BUY_STAT;
		}

		if( selector[1] == 0 ){
			if( userInp == 'k' ){
				DecrementIntLoop(selector[0], NUM_STATS-1);
			} else if( userInp == 'j' ){
				IncrementIntLoop(selector[0], NUM_STATS-1);
			} else if( userInp == 'H' ){
				player.SetStat(selector[0], -1);
			} else if( userInp == 'L' ){
				player.SetStat(selector[0], 1);
			}
		} else if( selector[1] == 1 ){
			if( userInp == 'k' ){
				DecrementIntLoop(selector[2], num_talents_in_stat);
			} else if( userInp == 'j' ){
				IncrementIntLoop(selector[2], num_talents_in_stat);
			} else if( userInp == 'H' ){
				player.RemoveTalentSpent(selector);
			} else if( userInp == 'L' ){
				player.AddTalentSpent(selector);
			}
		}
		break;

//i1.1
	case STATE_LEVELUP:
		PrintCurrentLevel(player, levelpos);
		PrintLevelUp(player, statpos, selector);		//magic number
		PrintPotentialTalentPoints(player, statpos, 1);
		PrintHelp(tooltip_pos, 1);
		userInp = GetUserInp(8, 'c', 'h', 'l', 'H', 'j', 'k', 'L', 'a');
		if( userInp == 'c' ){
			curstate = STATE_STATS;
		} else if( userInp == 'a' ){
			curstate = STATE_STATS;
			selector[1] = 0;
			player.Levelup();
			player.ConvertPotentialTalentPoints();
		} else if( userInp == 'k' ){
			if( selector[0] == 0 )
				selector[0] = NUM_STATS - 1;
			else
				selector[0]--;
		} else if( userInp == 'j' ){
			if( selector[0] == NUM_STATS - 1 )
				selector[0] = 0;
			else
				selector[0]++;
		} else if( (userInp == 'L') || (userInp == 'l') ){
			player.AddPotentialTalentPoint(selector);
		} else if( (userInp == 'H') || (userInp == 'h') ){
			player.RemovePotentialTalentPoint(selector);
		}
		break;

//i1.2
	case STATE_BUY_STAT:
		PrintCurrentLevel(player, levelpos);
		PrintStatBuy(player, statpos, selector);		//magic number
		PrintPotentialStats(player, statpos, 1);
		PrintHelp(tooltip_pos, 1);
		userInp = GetUserInp(8, 'c', 'h', 'l', 'H', 'j', 'k', 'L', 'a');
		if( userInp == 'c' ){
			curstate = STATE_STATS;
		} else if( userInp == 'a' ){
			curstate = STATE_STATS;
			selector[1] = 0;
			player.ConvertPotentialStats();
		} else if( userInp == 'k' ){
			if( selector[0] == 0 )
				selector[0] = NUM_STATS - 1;
			else
				selector[0]--;
		} else if( userInp == 'j' ){
			if( selector[0] == NUM_STATS - 1 )
				selector[0] = 0;
			else
				selector[0]++;
		} else if( (userInp == 'L') || (userInp == 'l') ){
			player.AddPotentialStat(selector[0]);
		} else if( (userInp == 'H') || (userInp == 'h') ){
			player.RemovePotentialStat(selector[0]);
		}
		break;

	default:
		break;
	}
}

void IncrementInt(int& i, int m){
	if( i < m )
		i++;
}

void IncrementIntLoop(int& i, int m){
	if( i == m )
		i = 0;
	else
		i++;
}

void DecrementInt(int& i, int m){
	if( i > m )
		i--;
}

void DecrementIntLoop(int& i, int m){
	if( i == 0 )
		i = m;
	else
		i--;
}

TalentTree* InitTalents(){
	TalentTree* tt = new TalentTree;
	tt->AddTalent(0, "Puglism", "Unarmed damage.");
	tt->AddTalent(0, "Headhunter", "Throwing damage.");
	tt->AddTalent(0, "Warrior", "Weapon damage.");
	tt->AddTalent(0, "Mule", "Carry weight.");
	tt->AddTalent(0, "Way of the Frog", "Jumping increase.");
	tt->AddTalent(0, "Way of the Ram", "Knockback increase.");
	tt->AddTalent(0, "Nutcracker", "Grip strength.");
	tt->AddTalent(1, "Mist", "Chance to dodge.");
	tt->AddTalent(1, "Exploiter", "Chance for subcrit.");
	tt->AddTalent(1, "Accuracy M.", "Chance to Hit (Melee weapons).");
	tt->AddTalent(1, "Accuracy R.", "Chance to Hit (Ranged weapons).");
	tt->AddTalent(1, "Accuracy T.", "Chance to Hit (Thrown weapons).");
	tt->AddTalent(1, "Speedster", "Movement speed increase.");
	tt->AddTalent(1, "Sealegs", "Chance to maintain balance.");
	tt->AddTalent(1, "Featherfall", "Reduced fall damage.");
	tt->AddTalent(1, "Ballistics", "Increase projectile range.");
	tt->AddTalent(1, "Avoidance", "Increased saving throw on AoE effects.");
	tt->AddTalent(2, "Hearty", "Health increase.");
	tt->AddTalent(2, "Healthy", "Resistance increase (Bleeding, Poison, Disease).");
	tt->AddTalent(2, "Aegis", "Chance to deflect damage type.");
	tt->AddTalent(2, "Mouth Breather", "Reduced DoT from neck Constriction.");
	tt->AddTalent(2, "Drunkard", "Drinking tolerance.");
	tt->AddTalent(2, "Poise", "Resistance to knockback.");
	tt->AddTalent(2, "Castle", "Make yourself cover for allies.");
	tt->AddTalent(3, "Empty Mind", "Buff duration increase.");
	tt->AddTalent(3, "Magician", "All spell damage increase.");
	tt->AddTalent(3, "Accuracy S.", "Chance to Hit (Spells).");
	tt->AddTalent(3, "Firebender", "Fire and Lightning damage increase.");
	tt->AddTalent(3, "Ice Maiden", "Ice damage increase.");
	tt->AddTalent(3, "Necromancer", "Necrotic damage increase.");
	tt->AddTalent(3, "The Faithful", "Radiant damage increase.");
	tt->AddTalent(3, "Melting Man", "Acid damage increase.");
	tt->AddTalent(4, "Strong Mind", "Increase DC spell break saves.");
	tt->AddTalent(4, "Watch Your Step!", "Chance to spot traps passively.");
	tt->AddTalent(4, "Show Yourself!", "Chance to spot hidden movements passively.");
	tt->AddTalent(4, "The Doctor", "Increase spell healing.");
	tt->AddTalent(4, "Druidic", "Increased offensive nature damage.");
	tt->AddTalent(4, "Magic Mirror", "Chance to deflect small magic projectiles.");
	tt->AddTalent(4, "Writer's Block", "Chance to gain insight while crafting.");
	tt->AddTalent(5, "Knock Knock,", "Chance to be funny.");
	tt->AddTalent(5, "Who's There?", "Chance to persuade door.");
	tt->AddTalent(5, "Charge!", "Chance for nearby allies to roll +1 initiative.");
	tt->AddTalent(5, "Attack!", "Chance for nearby allies to increase primary damage stat +1.");
	tt->AddTalent(5, "Hold the Line!", "Chance for nearby allies to increase AC +1.");
	tt->AddTalent(5, "Presence", "Increased threat.");
	tt->AddTalent(5, "Distract", "Chance to decrease threat for one turn.");
	tt->AddTalent(5, "Bully", "psychic damage increase.");
	tt->AddTalent(6, "Luck", "Lucky.");
	return tt;
}
