#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/lib.h"

PlayerCharacter::PlayerCharacter()
: level(0) {
	for( int i=0; i<NUM_STATS; i++ ){
		stat[i] = 0;
		talent_point[i] = 0;
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
		if( stat[i] > 18 ){
			dice_thrown = 6;
		} else if( stat[i] > 16 ){
			dice_thrown = 5;
		} else if( stat[i] > 14 ){
			dice_thrown = 4;
		} else if( stat[i] > 12 ){
			dice_thrown = 3;
		} else if( stat[i] > 10 ){
			dice_thrown = 2;
	} else if( stat[i] > 7 ){
			dice_thrown = 1;
		}

		for( int j=0; j<dice_thrown; j++ ){
			talent_point[i] += rand_num(1, 4);
		}
	}
}

void PlayerCharacter::SetStat(int i, int n){
	stat[i] += n;
}

int PlayerCharacter::GetLevel(){
	return level;
}

int PlayerCharacter::GetStat(int i){
	return stat[i];
}

int PlayerCharacter::GetTalentPoint(int i){
	return talent_point[i];
}
