#include <curses.h>
#include <random>
#include <string>
#include "../include/lib.h"

const int NUM_TALENTS_IN_STAT[] = {NUM_STR_TALENTS, NUM_DEX_TALENTS, NUM_CON_TALENTS, NUM_INT_TALENTS, NUM_WIS_TALENTS, NUM_CHA_TALENTS, 1};

const std::string STAT_NAMES[] = {
	"STR",
	"DEX",
	"CON",
	"INT",
	"WIS",
	"CHA",
	"LCK"
};

const std::string STAT_NAMES_LONG[] = {
	"strength",
	"dexterity",
	"constitution",
	"intelligence",
	"wisdom",
	"charisma",
	"luck"
};

std::random_device rd;
std::mt19937 RNGine(rd());
int rand_num(int min, int max){
	std::uniform_int_distribution<int> rand(min, max);
	return rand(RNGine);
}

char GetUserInp(int argn, ...){
	char userInp;
	while(true) {
		userInp = getch();
		va_list args;
		va_start(args, argn);
		for( int i=0; i<argn; i++ ){
			if( userInp == va_arg(args, int) ){
				va_end(args);
				return userInp;
			}
		}
	}
}

Talent::Talent()
: level(0), name("N/A"), desc("N/A") {}

Talent::Talent(int s, std::string n, std::string d)
: level(s), name(n), desc(d) {}

Talent::~Talent(){}

Talent* Talent::GetNext(){
	return next;
}

void Talent::SetNext(Talent* new_next){
	next = new_next;
}

std::string Talent::GetName(){
	return name;
}

int Talent::GetLevel(){
	return level;
}

std::string Talent::GetDesc(){
	return desc;
}

TalentTree::TalentTree() { }


TalentTree::~TalentTree() { }

void TalentTree::AddTalent(int s, std::string name, std::string desc){
	Talent* new_talent = new Talent(s, name, desc);
	if( head[s] == nullptr ){
		head[s] = new_talent;
		return;
	}

	Talent* temp = head[s];
	while( temp->GetNext() != nullptr ){
		temp = temp->GetNext();
	}

	temp->SetNext(new_talent);
}

int TalentTree::GetTalentLevel(int s, int n){
	int counter = 0;
	Talent* temp = head[s];

	if( head[s] == nullptr ){
		return -1;
	}

	while( temp->GetNext() != nullptr ){
		if( counter == n ){
			break;
		}
		temp = temp->GetNext();
		counter++;
	}

	return temp->GetLevel();
}

std::string TalentTree::GetTalentName(int s, int n){
	int counter = 0;
	Talent* temp = head[s];

	if( head[s] == nullptr ){
		return "ERROR: head is nullptr";
	}

	while( temp->GetNext() != nullptr ){
		if( counter == n ){
			break;
		}
		temp = temp->GetNext();
		counter++;
	}

	return temp->GetName();
}

std::string TalentTree::GetTalentDesc(int s, int n){
	int counter = 0;
	Talent* temp = head[s];

	if( head[s] == nullptr ){
		return "ERROR: head is nullptr";
	}

	while( temp->GetNext() != nullptr ){
		if( counter == n ){
			break;
		}
		temp = temp->GetNext();
		counter++;
	}

	return temp->GetDesc();
}

