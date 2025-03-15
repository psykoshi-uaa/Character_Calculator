#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/lib.h"

PlayerCharacter::PlayerCharacter()
: level(0), talent(nullptr) {
	for( int i=0; i<NUM_STATS; i++ ){
		stat[i] = 0;
		talent_point[i] = 0;
		talent_point[i] = 0;
	}
}

PlayerCharacter::PlayerCharacter(std::string n, TalentTree* t)
: level(0), name(n), talent(nullptr) {
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
		if( stat[i] > 18 ){
			talent_point[i] += rand_num(1, 8);
			talent_point[i] += rand_num(1, 8);
		} else if( stat[i] > 16 ){
			talent_point[i] += rand_num(1, 12);
		} else if( stat[i] > 14 ){
			talent_point[i] += rand_num(1, 10);
		} else if( stat[i] > 12 ){
			talent_point[i] += rand_num(1, 8);
		} else if( stat[i] > 10 ){
			talent_point[i] += rand_num(1, 6);
		} else if( stat[i] > 7 ){
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

int PlayerCharacter::GetTalentPoint(int i) {
	return talent_point[i];
}

int PlayerCharacter::GetTalentLevel(int s, std::string n) {
	int level = 0;
	Talent* temp = talent;
	if( talent != nullptr ){
		while( temp->GetNext() != nullptr ){
			if( temp->GetName() == n ){
				level = temp->GetLevel();
			}
			temp = temp->GetNext();
		}
	}
	return level;
}
