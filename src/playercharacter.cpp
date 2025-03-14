#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/lib.h"

PlayerCharacter::PlayerCharacter()
: level(0) {
	pos = {1, 1};
	for( int i=0; i<NUM_STATS; i++ ){
		stats[i] = 0;
		talent_points[i] = 0;
	}
}

PlayerCharacter::~PlayerCharacter(){
}

void PlayerCharacter::Levelup(){
	GenerateTalentPoints();
	level += 1;
}

void PlayerCharacter::GenerateTalentPoints(){
	for( int i=0; i<NUM_STATS; i++ ){
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

void PlayerCharacter::SetPos(struct Pos new_pos){
	pos = new_pos;
}

void PlayerCharacter::PrintCurrentLevel(){
	mvprintw(pos.y, pos.x + 4, "LEVEL: %i", level);
}
