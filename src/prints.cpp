#include "../include/prints.h"
#include "../include/pos.h"
#include "../include/cwin.h"
#include "../include/lib.h"
#include "../include/playercharacter.h"


void PrintStatNames(struct Pos pos, int* s){
	struct Pos new_pos = pos;
	for( int i=0; i<NUM_STATS; i++ ){
		int col = i+1;
		if( (i == s[0]) && (s[1] == 0) ){
			col += 7;
			mvprintw(new_pos.y, pos.x - 4, "-->");
		}
		attron(COLOR_PAIR(col));
		mvaddstr(new_pos.y, new_pos.x, STAT_NAMES[i].c_str());
		attroff(COLOR_PAIR(col));
		new_pos.y += STAT_MARGIN_Y;
	}
}

void PrintStatDescription(struct Pos pos, int stat){
	switch( stat ){
	case 0:
		mvprintw(pos.y, pos.x, "Strength determines a characters physical might.");
		break;
	
	case 1:
		mvprintw(pos.y, pos.x, "Dexterity determines a characters reflexes");
		break;
	
	case 2:
		mvprintw(pos.y, pos.x, "Constitution determines a characters vigor");
		break;
	
	case 3:
		mvprintw(pos.y, pos.x, "Intelligence determines a characters mental aptitude");
		break;
	
	case 4:
		mvprintw(pos.y, pos.x, "Wisdom determines a characters mental fortitude");
		break;
	
	case 5:
		mvprintw(pos.y, pos.x, "Charisma determines a characters charm and leadership");
		break;

	case 6:
		mvprintw(pos.y, pos.x, "Luck determines a characters luck");
		break;

	default:
		break;
	}
}

void PrintCurrentLevel(PlayerCharacter player, struct Pos pos){
	mvprintw(pos.y, pos.x, "LEVEL: %i", player.GetLevel());
}

void PrintCurrentStats(Cwin* statwin, PlayerCharacter player, struct Pos pos, int s){
	int statx = 0;
	struct Pos new_pos = pos;
	new_pos.x += 3;
	for( int i=0; i<NUM_STATS; i++ ){
		statwin->Moveto({new_pos.y, pos.x});
		statwin->Print();

		if( player.GetStat(i) > 9 )
			statx = -1;
		else
			statx = 0;

		if( i == s ){
			attron(COLOR_PAIR(14));
			mvprintw(new_pos.y + 2, new_pos.x + statx, "%i", player.GetStat(i));
			attroff(COLOR_PAIR(14));
		} else
			mvprintw(new_pos.y + 2, new_pos.x + statx, "%i", player.GetStat(i));

		new_pos.y += STAT_MARGIN_Y;
	}
}

void PrintAvailableTalentPoints(PlayerCharacter player, struct Pos pos){
	struct Pos new_pos = pos;
	new_pos.x += 0;
	new_pos.y += 1;
	for( int i=0; i<NUM_STATS; i++ ){
		mvprintw(new_pos.y, new_pos.x, "talent points: %i", player.GetTalentPoint(i));
		new_pos.y += STAT_MARGIN_Y;
	}
}

void PrintStatTalents(TalentTree* tt, PlayerCharacter player, struct Pos pos, int* s){
	struct Pos new_pos = pos;
	for( int i=0; i<NUM_TALENTS_IN_STAT[s[0]]; i++ ){
		mvprintw(new_pos.y + i, pos.x + 4, "%s", tt->GetTalentName(s[0], i).c_str());
		if( (s[2] == i) && (s[1] == 1) ){
			mvprintw(new_pos.y+i, pos.x, "-->");
			attron(COLOR_PAIR(14));
			mvprintw(new_pos.y+i, pos.x + 4, "%s", tt->GetTalentName(s[0], i).c_str());
			attroff(COLOR_PAIR(14));
		} else
			mvprintw(new_pos.y+i, pos.x + 4, "%s", tt->GetTalentName(s[0], i).c_str());
		new_pos.y += DESC_MARGIN_Y;
	}
}

void PrintStatTalentsDesc(TalentTree* tt, struct Pos pos, int* s){
	mvprintw(pos.y, pos.x, "%s", tt->GetTalentDesc(s[0], s[2]).c_str());
	/*
	struct Pos new_pos = pos;
	for( int i=0; i<NUM_TALENTS_IN_STAT[s[0]]; i++ ){
		mvprintw(new_pos.y + i, pos.x, "%s", tt->GetTalentDesc(s[0], i).c_str());
		new_pos.y += DESC_MARGIN_Y;
	}
	*/
}
