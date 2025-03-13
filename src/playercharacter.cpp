#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/tools.h"

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
	SetTalentWind();
}

PlayerCharacter::~PlayerCharacter(){
}

void PlayerCharacter::SetTalentWind(){
	int num_talents[] = {NUM_STR_TALENTS, NUM_DEX_TALENTS, NUM_CON_TALENTS, NUM_INT_TALENTS, NUM_WIS_TALENTS, NUM_CHA_TALENTS};
	for( int i=0; i<NUM_OF_STATS; i++ ){
		talent_wind[i] = new Cwind(SIZE_TALENT_MENU_H, SIZE_TALENT_MENU_W, num_talents[i], pos.y, pos.x);
		talent_wind[i]->set_title(STAT_NAMES[i]);
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
	struct Vector temp_pos = {pos.y + 10, pos.x};
	mvaddstr(temp_pos.y, temp_pos.x, "talent points:");
	for( int i=0; i<NUM_OF_STATS; i++ ){
		mvaddstr(temp_pos.y + 1 + i, temp_pos.x, STAT_NAMES[i]);
		mvprintw(temp_pos.y + 1 + i, temp_pos.x + 5, "%i", talent_points[i]);
	}
}

void PlayerCharacter::PrintTalents(){
	Vector offset = { 0 };
	int margin = 25;
	talent_wind[0]->print();
}
