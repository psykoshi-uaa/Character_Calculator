#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/lib.h"

PlayerCharacter::PlayerCharacter()
: level(0) {
	pos = {1, 1};
	for( int i=0; i<NUM_OF_STATS; i++ ){
		stats[i] = 0;
		talent_points[i] = 0;
		for( int j=0; j<TOTAL_TALENTS; j++ ){
			talents_pointed[i][j] = 0;
		}
	}
	SetStatWind();
	SetTalentWind();
}

PlayerCharacter::~PlayerCharacter(){
}

void PlayerCharacter::SetStatWind(){
	for( int i=0; i<NUM_OF_STATS; i++ ){
		stat_wind[i] = new Cwind(SIZE_TALENT_MENU_H, SIZE_TALENT_MENU_W, NUM_TALENTS[i], pos.y, pos.x);
		stat_wind[i]->SetTitle(STAT_NAMES[i]);
		stat_wind[i]->Moveto(pos.y + 10, pos.x);
	}
}

void PlayerCharacter::SetTalentWind(){
	for( int i=0; i<NUM_OF_STATS; i++ ){
		talent_wind[i] = new Cwind(SIZE_TALENT_MENU_H, SIZE_TALENT_MENU_W, NUM_TALENTS[i], pos.y, pos.x);
		talent_wind[i]->SetTitle(STAT_NAMES[i]);
		talent_wind[i]->Moveto(pos.y + 10, pos.x);
	}
}

void PlayerCharacter::Levelup(){
	GenerateTalentPoints();
	level += 1;
}

void PlayerCharacter::GenerateTalentPoints(){
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

void PlayerCharacter::SetPosition(int y, int x){
	pos = {y, x};
}

void PlayerCharacter::PrintCurrentLevel(){
	mvprintw(pos.y, pos.x + 4, "LEVEL: %i", level);
}

void PlayerCharacter::PrintStats(){
	struct Vector temp_pos = {pos.y + 2, pos.x};
	mvaddstr(temp_pos.y, temp_pos.x, "stats:");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvaddstr(temp_pos.y + 1 + i, temp_pos.x, STAT_NAMES[i]);
		mvprintw(temp_pos.y + 1 + i, temp_pos.x + 5, "%i", stats[i]);
	}
}

void PlayerCharacter::PrintTalentPoints(){
	struct Vector temp_pos = {pos.y + 2, pos.x};
	mvaddstr(temp_pos.y, temp_pos.x, "talent points:");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvaddstr(temp_pos.y + 1 + i, temp_pos.x, STAT_NAMES[i]);
		mvprintw(temp_pos.y + 1 + i, temp_pos.x + 5, "%i", talent_points[i]);
	}
}

void PlayerCharacter::PrintTalent(int y, int x, int t){
	struct Vector offset = { 3, 2 };
	for( int i=0; i<NUM_TALENTS[t]; i++  ){
		offset.x = 2;
		mvprintw(y + offset.y + i, x + offset.x, "[%i]", talent_points[i]);
		offset.x += 4;
		for(int j=0; j<256; j++ ){
			if( TALENT_NAMES[i][j] == '\0' ){
				break;
			}
			mvprintw(y + offset.y + i, x + offset.x, "%c", TALENT_NAMES[i][j]);
			offset.x++;
		}
	}
}

void PlayerCharacter::PrintTalents(){
	Vector offset = { 0 };
	int margin = 25;
	talent_wind[0]->Print();
	PrintTalent(talent_wind[0]->Gety(), talent_wind[0]->Getx(), 0);
}
