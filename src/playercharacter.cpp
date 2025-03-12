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
