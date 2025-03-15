#include <curses.h>
#include <random>
#include <string>
#include "../include/lib.h"

const int NUM_TALENTS_IN_STAT[] = {NUM_STR_TALENTS, NUM_DEX_TALENTS, NUM_CON_TALENTS, NUM_INT_TALENTS, NUM_WIS_TALENTS, NUM_CHA_TALENTS};

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
				clear();
				va_end(args);
				return userInp;
			}
		}
	}
}

Talent::Talent()
: stat(0), name("N/A"), desc("N/A") {}

Talent::Talent(int s, std::string n, std::string d)
: stat(s), name(n), desc(d) {}

Talent::~Talent(){}

Talent* Talent::GetNext(){
	return next;
}

void Talent::SetNext(Talent* new_next){
	next = new_next;
}

SubTalentTree::SubTalentTree()
: stat(0){
	head = new Talent;
}

SubTalentTree::SubTalentTree(int s)
: stat(s){}

SubTalentTree::~SubTalentTree() {}

void SubTalentTree::AddTalent(std::string name, std::string desc) {
	Talent* temp = head;
	if( head == nullptr ){
		head = new Talent(stat, name, desc);
		return;
	}

	while( temp->GetNext() != nullptr ){
		temp = temp->GetNext();
	}
	temp->SetNext(new Talent(stat, name, desc));
}

void SubTalentTree::PrintTalents(){
	
}

TalentTree::TalentTree() {
	for( int i=0; i<NUM_STATS; i++ ){
		stt[i] = new SubTalentTree(0);
	}
}

TalentTree::~TalentTree() {
	for( int i=0; i<NUM_STATS; i++ ){
		//delete stt[i];
	}
}

void TalentTree::AddTalent(int stat, std::string name, std::string desc){
	stt[stat]->AddTalent(name, desc);
}
