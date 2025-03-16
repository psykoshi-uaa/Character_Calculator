#include <curses.h>
#include "../include/playercharacter.h"
#include "../include/lib.h"

PlayerCharacter::PlayerCharacter()
: level(0), talent(nullptr), stat_points(0) {
	for( int i=0; i<NUM_STATS; i++ ){
		stat[i] = 8;
		stat_points = 27;
		stat[NUM_STATS-1] = 0;
		potential_stat[i];
		talent_point[i] = 0;
		potential_talent_point[i] = 1;
		potential_talent_point[NUM_STATS-1] = 0;
		for( int j=0; j<MAX_TALENTS; j++ ){
			talent_spent[i][j] = 0;
		}
	}
}

PlayerCharacter::PlayerCharacter(std::string n, TalentTree* t)
: level(0), name(n), talent(nullptr), stat_points(0) {
	for( int i=0; i<NUM_STATS; i++ ){
		stat[i] = 8;
		stat_points = 27;
		stat[NUM_STATS-1] = 0;
		potential_stat[i];
		talent_point[i] = 0;
		potential_talent_point[i] = 1;
		potential_talent_point[NUM_STATS-1] = 0;
	}
}

PlayerCharacter::~PlayerCharacter(){
}

void PlayerCharacter::Levelup(){
	if( level < 20 )
		level += 1;
}

void PlayerCharacter::AddPotentialTalentPoint(int* s){
	for( int i=0; i<NUM_STATS; i++ ){
		if( s[0] == i  ){
			if( (stat[i] >= 20) && (potential_talent_point[i] < 16) )
				potential_talent_point[i]++;
			else if( (stat[i] >= 18) && (potential_talent_point[i] < 12) )
				potential_talent_point[i]++;
			else if( (stat[i] >= 14) && (potential_talent_point[i] < 10) )
				potential_talent_point[i]++;
			else if( (stat[i] >= 11) && (potential_talent_point[i] < 8) )
				potential_talent_point[i]++;
			else if( (stat[i] >= 8) && (potential_talent_point[i] < 6) )
				potential_talent_point[i]++;
		}
	}
}

void PlayerCharacter::RemovePotentialTalentPoint(int* s){
	for( int i=0; i<NUM_STATS; i++ ){
		if( (s[0] == i) && (potential_talent_point[s[0]] > 1) )
			potential_talent_point[i]--;
	}
}

void PlayerCharacter::ConvertPotentialTalentPoints(){
	for( int i=0; i<NUM_STATS; i++ ){
		talent_point[i] += potential_talent_point[i];
		if( stat[i] < 8 )
			potential_talent_point[i] = 0;
		else
			potential_talent_point[i] = 1;
	}
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

void PlayerCharacter::SetPotentialTalentPoints(){
	for( int i=0; i<NUM_STATS; i++ ){
		potential_talent_point[i] = 1;
	}
}

void PlayerCharacter::SetPotentialStats(){
	for( int i=0; i<NUM_STATS; i++ ){
		potential_stat[i] = stat[i];
	}
}

void PlayerCharacter::AddPotentialStat(int i){
	int cost = 0;
	if( potential_stat[i] + 1 == 14 ){
		cost = 7;
	} else if( potential_stat[i] + 1 == 15 ){
		cost = 9;
	} else if( potential_stat[i] + 1 >= 8 ){
		cost = potential_stat[i] + 1 - 8;
	} else {
		cost = 1;
	}

	if( stat_points - cost >= 0 ){
		potential_stat[i]++;
		stat_points -= cost;
	}
}

void PlayerCharacter::RemovePotentialStat(int i){
	int cost = 0;
	if( potential_stat[i] == 14 ){
		cost = 7;
	} else if( potential_stat[i] == 15 ){
		cost = 9;
	} else if( potential_stat[i] >= 8 ){
		cost = potential_stat[i] - 8;
	} else {
		cost = 1;
	}
	if( potential_stat[i] > stat[i] ){
		potential_stat[i]--;
		stat_points += cost;
	}
}

void PlayerCharacter::ConvertPotentialStats(){
	for( int i=0; i<NUM_STATS; i++ ){
		stat[i] = potential_stat[i];
	}
}

void PlayerCharacter::AddTalentSpent(int* s){
	int cost = 1;
	if( talent_spent[s[0]][s[2]] >= 14 ){
		cost = 6;
	} else if( talent_spent[s[0]][s[2]] >= 10 ){
		cost = 5;
	} else if( talent_spent[s[0]][s[2]] >= 8 ){
		cost = 4;
	} else if( talent_spent[s[0]][s[2]] >= 5 ){
		cost = 3;
	} else if( talent_spent[s[0]][s[2]] >= 3 ){
		cost = 2;
	}

	if( talent_point[s[0]] - cost >= 0 ){
		talent_spent[s[0]][s[2]]++;
		talent_point[s[0]] -= cost;
	}
}

void PlayerCharacter::RemoveTalentSpent(int* s){
	int cost = 1;
	if( talent_spent[s[0]][s[2]] >= 15 ){
		cost = 6;
	} else if( talent_spent[s[0]][s[2]] >= 11 ){
		cost = 5;
	} else if( talent_spent[s[0]][s[2]] >= 9 ){
		cost = 4;
	} else if( talent_spent[s[0]][s[2]] >= 6 ){
		cost = 3;
	} else if( talent_spent[s[0]][s[2]] >= 4 ){
		cost = 2;
	}

	if( talent_spent[s[0]][s[2]] > 0 ){
		talent_spent[s[0]][s[2]]--;
		talent_point[s[0]] += cost;
	}
}

int PlayerCharacter::GetLevel(){
	return level;
}

int PlayerCharacter::GetStat(int i){
	return stat[i];
}

int PlayerCharacter::GetPotentialStat(int i){
	return potential_stat[i];
}

int PlayerCharacter::GetPotentialStatCost(int i){
	int cost = 0;
	if( potential_stat[i] + 1 == 14 ){
		cost = 7;
	} else if( potential_stat[i] + 1 == 15 ){
		cost = 9;
	} else if( potential_stat[i] + 1 >= 8 ){
		cost = potential_stat[i] + 1 - 8;
	} else {
		cost = 1;
	}
	return cost;
}

int PlayerCharacter::GetStatPoints(){
	return stat_points;
}

int PlayerCharacter::GetTalentPoint(int i) {
	return talent_point[i];
}

int PlayerCharacter::GetPotentialTalentPoint(int i) {
	return potential_talent_point[i];
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

int PlayerCharacter::GetTalentSpent(int* s, int i){
	return talent_spent[s[0]][i];
}
