#include <curses.h>
#include <stdio.h>
#include <random>
#include <cmath>
#include <string>

#define NUM_STATS 7
#define NUM_TALENTS 48
#define NUM_STR_TALENTS 7
#define NUM_DEX_TALENTS 10
#define NUM_CON_TALENTS 7
#define NUM_INT_TALENTS 8
#define NUM_WIS_TALENTS 7
#define NUM_CHA_TALENTS 8
#define NUM_LCK_TALENTS 1
#define MAX_TALENTS 10

#define SIZE_TALENT_MENU_H 16
#define SIZE_TALENT_MENU_W 24
#define SIZE_SIZE_MENU_H 9
#define SIZE_SIZE_MENU_W 9
#define STAT_MARGIN_Y 4
#define DESC_MARGIN_Y 1
#define TALENT_DICE_BRACKETS 6

struct Pos {
	int y;
	int x;
};

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

const std::string TALENT_DICE[] = {
	"Too Low",
	"1D6",
	"1D8",
	"1D10",
	"1D12",
	"2D8"
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

int rand_num(int min, int max);
char GetUserInp(int argn, ...);
void PrintLevelupPrompt(int y, int x);

enum AppState { STATE_CHAR_CREATION, STATE_STATS, STATE_BUY_STAT, STATE_TALENTS, STATE_LEVELUP, STATE_RESET, STATE_EXIT };
//enum StatState { STATE_STR, STATE_DEX, STATE_CON, STATE_INT, STATE_WIS, STATE_CHA, STATE_LCK };

class Talent {
private:
	int level;
	std::string name;
	std::string desc;
	Talent* next;
public:
	Talent();
	Talent(int s, std::string n, std::string d);
	~Talent();
	Talent* GetNext();
	int GetLevel();
	void SetNext(Talent* new_next);
	std::string GetName();
	std::string GetDesc();
};

class TalentTree {
private:
	Talent* head[NUM_STATS];
public:
	TalentTree();
	~TalentTree();
	void AddTalent(int stat, std::string name, std::string desc);
	int GetTalentLevel(int s, int n);
	std::string GetTalentName(int s, int n);
	std::string GetTalentDesc(int s, int n);
};

class Cwin {
private:
	struct Pos pos;
	struct Pos size;
	void AdjustHeight(int h);
	void AdjustWidth(int w);
	
public:
	Cwin();
	Cwin(int h, int w, int y, int x);
	~Cwin();
	void Print();
	void Moveto(struct Pos pos);
	void Shiftx(int x=0);
	void Shifty(int y=0);
	void AdjustSize(int h, int x);
	int Gety();
	int Getx();
};

class PlayerCharacter {
private:
	std::string name;
	int level;
	int stat[NUM_STATS];
	int stat_points;
	int potential_stat[NUM_STATS];
	int talent_point[NUM_STATS];
	int potential_talent_point[NUM_STATS];
	int talent_spent[NUM_STATS][MAX_TALENTS];
	Talent* talent;
	Cwin* stat_win[NUM_STATS];
	Cwin* talent_win;

public:
	PlayerCharacter();
	PlayerCharacter(std::string n, TalentTree* t);
	~PlayerCharacter();
	void Levelup();
	void SetPotentialTalentPoints();
	void AddPotentialTalentPoint(int* s);
	void RemovePotentialTalentPoint(int* s);
	void ConvertPotentialTalentPoints();
	void GenerateTalentPoints();
	void SetStat(int stat, int n);
	void SetPotentialStats();
	void AddPotentialStat(int i);
	void RemovePotentialStat(int i);
	void ConvertPotentialStats();
	void AddTalentSpent(int* s);
	void RemoveTalentSpent(int* s);
	int GetLevel();
	int GetStat(int i);
	int GetStatPoints();
	int GetPotentialStat(int i);
	int GetPotentialStatCost(int i);
	int GetTalentPoint(int i);
	int GetPotentialTalentPoint(int i);
	int GetTalentLevel(int s, std::string n);
	int GetTalentSpent(int* s, int i);
};

void StateMachine(TalentTree* tt, Cwin* cwin[3], PlayerCharacter& player, AppState& curstate, int* selector, char& userInp, struct Pos tooltip_pos);
void IncrementInt(int& i, int m);
void DecrementInt(int& i, int m);
void IncrementIntLoop(int& i, int m);
void DecrementIntLoop(int& i, int m);
TalentTree* InitTalents();
void PrintStatNames(struct Pos pos, int* s, int m);
void PrintTalentDiceRoll(PlayerCharacter player, struct Pos pos, int* s);
void PrintStatDescription(struct Pos pos, int stat);
void PrintAvailableTalentPoints(PlayerCharacter player, struct Pos pos);
void PrintPotentialTalentPoints(PlayerCharacter player, struct Pos pos, int m);
void PrintCurrentStats(Cwin* statwin, PlayerCharacter player, struct Pos pos, int s);
void PrintCurrentLevel(PlayerCharacter player, struct Pos pos);
void PrintStatTalents(TalentTree* tt, PlayerCharacter player, struct Pos pos, int* s);
void PrintStatTalentsDesc(TalentTree* tt, struct Pos pos, int* s);
void PrintLevelUp(PlayerCharacter player, struct Pos pos, int* s);
void PrintStatBuy(PlayerCharacter player, struct Pos pos, int* s);
void PrintPotentialStats(PlayerCharacter player, struct Pos pos, int m);
void PrintButton(int i, int* s, struct Pos pos, struct Pos size, std::string title);
void PrintTalentSpent(PlayerCharacter player, struct Pos pos, int* s);

void initialize(){
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
}

int deinitialize(){
	endwin();
	return 0;
}

int main(){
	initialize();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_BLACK, COLOR_CYAN);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	init_pair(14, COLOR_BLACK, COLOR_WHITE);

	enum AppState curstate = STATE_STATS;
	int selector[3] = { 0 };
	selector[2] = { -1 };
	char userInp = '\0';
	TalentTree* tt = InitTalents();

	struct Pos screensize = { 0 };
	getmaxyx(stdscr, screensize.y, screensize.x);
	screensize = {screensize.y-2, screensize.x-2};
	Cwin* cwin[3];
	cwin[0] = new Cwin(screensize.y, screensize.x, 1, 1);
	cwin[1] = new Cwin(4, 6, 7, 5);
	cwin[2] = new Cwin(30, 5, 20, 3);
	struct Pos tooltip_pos = { screensize.y-1, screensize.x/4};

	while( curstate != STATE_EXIT ){
		clear();
		PlayerCharacter player("Test McTestington", tt); 
		curstate = STATE_STATS;
		
		while( true ){
			StateMachine(tt, cwin, player, curstate, selector, userInp, tooltip_pos);
			if( (curstate == STATE_RESET) || (curstate == STATE_EXIT) )
				break;
		}
		if( curstate == STATE_EXIT )
			break;
	}
	return deinitialize();
}

void StateMachine(TalentTree* tt, Cwin* cwin[3], PlayerCharacter& player, AppState& curstate, int* selector, char& userInp, struct Pos tooltip_pos){
	struct Pos levelpos = { 1, 3 };
	struct Pos statpos = { 3, 7 };
	struct Pos talentpos = { 4, 27 };
	struct Pos descpos = { 4, 50 };
	int num_talents_in_stat = NUM_TALENTS_IN_STAT[selector[0]] - 1;
	int temp_sp = player.GetStatPoints();
	cwin[0]->Print();

//i1.0
	switch( curstate ){
	case STATE_STATS:
		PrintCurrentLevel(player, levelpos);
		PrintCurrentStats(cwin[1], player, statpos, -1);
		PrintStatNames(statpos, selector, STAT_MARGIN_Y);
		PrintAvailableTalentPoints(player, {statpos.y+2, statpos.x+7});
		PrintStatTalents(tt, player, talentpos, selector);
		PrintTalentSpent(player, talentpos, selector);
		if( selector[1] == 1 )
			PrintStatTalentsDesc(tt, tooltip_pos, selector);
		else
			PrintStatDescription(tooltip_pos, selector[0]);

		userInp = GetUserInp(12, 'h', 'j', 'k', 'l', 'q', 'H', 'L', 'T', 'R', 'e', 'b', 'p');
		if( userInp == 'q' ){
			curstate = STATE_EXIT;
		} else if( userInp == 'l'){
			if( selector[1] == 0 ){
				selector[2] = 0;
			}
			selector[1] = 1;
			IncrementInt(selector[1], 1);
		} else if( userInp == 'h'){
			if( selector[1] == 1 ){
				selector[2] = -1;
			}
			DecrementInt(selector[1], 0);

		} else if( userInp == 'R' ){
			curstate = STATE_RESET;
		} else if( userInp == 'T' ){
			selector[0] = 0;
			selector[1] = 0;
			player.SetPotentialTalentPoints();
			curstate = STATE_LEVELUP;
		} else if( userInp == 'p' ){
			selector[0] = 0;
			selector[1] = 0;
			player.SetPotentialStats();
			curstate = STATE_BUY_STAT;
		}

		if( selector[1] == 0 ){
			if( userInp == 'k' ){
				DecrementIntLoop(selector[0], NUM_STATS-1);
			} else if( userInp == 'j' ){
				IncrementIntLoop(selector[0], NUM_STATS-1);
			}
		} else if( selector[1] == 1 ){
			if( userInp == 'k' ){
				DecrementIntLoop(selector[2], num_talents_in_stat);
			} else if( userInp == 'j' ){
				IncrementIntLoop(selector[2], num_talents_in_stat);
			} else if( userInp == 'H' ){
				player.RemoveTalentSpent(selector);
			} else if( userInp == 'L' ){
				player.AddTalentSpent(selector);
			}
		}
		break;

//i1.1
	case STATE_LEVELUP:
		PrintCurrentLevel(player, levelpos);
		PrintLevelUp(player, statpos, selector);		//magic number
		PrintPotentialTalentPoints(player, statpos, 1);
		userInp = GetUserInp(6, 'c', 'h', 'j', 'k', 'l', 'T');
		if( userInp == 'c' ){
			curstate = STATE_STATS;
		} else if( userInp == 'T' ){
			curstate = STATE_STATS;
			selector[1] = 0;
			player.Levelup();
			player.ConvertPotentialTalentPoints();
		} else if( userInp == 'k' ){
			if( selector[0] == 0 )
				selector[0] = NUM_STATS - 1;
			else
				selector[0]--;
		} else if( userInp == 'j' ){
			if( selector[0] == NUM_STATS - 1 )
				selector[0] = 0;
			else
				selector[0]++;
		}else if( userInp == 'l' ){
			player.AddPotentialTalentPoint(selector);
		} else if( userInp == 'h' ){
			player.RemovePotentialTalentPoint(selector);
		}
		break;

//i1.2
	case STATE_BUY_STAT:
		PrintCurrentLevel(player, levelpos);
		PrintStatBuy(player, statpos, selector);		//magic number
		PrintPotentialStats(player, statpos, 1);
		userInp = GetUserInp(6, 'c', 'h', 'j', 'k', 'l', 'T');
		if( userInp == 'c' ){
			curstate = STATE_STATS;
		} else if( userInp == 'T' ){
			curstate = STATE_STATS;
			selector[1] = 0;
			player.ConvertPotentialStats();
		} else if( userInp == 'k' ){
			if( selector[0] == 0 )
				selector[0] = NUM_STATS - 1;
			else
				selector[0]--;
		} else if( userInp == 'j' ){
			if( selector[0] == NUM_STATS - 1 )
				selector[0] = 0;
			else
				selector[0]++;
		}else if( userInp == 'l' ){
			player.AddPotentialStat(selector[0]);
		} else if( userInp == 'h' ){
			player.RemovePotentialStat(selector[0]);
		}
		break;

	default:
		break;
	}
}

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

Cwin::Cwin() {
	pos = { 0 };
	size = { 5, 5 };
}

Cwin::Cwin(int h, int w, int y, int x) {
	pos = { y, x };
	size = { h, w };
}

Cwin::~Cwin(){}


void Cwin::AdjustHeight(int h) {
	if( h < 2 ){
		size.y = 2;
		return;
	}
	size.y = h;
}

void Cwin::AdjustWidth(int w) {
	if( w < 3 ){
		size.x = 3;
		return;
	} else {
		if( size.x % 2 == 0 ){
			size.x = w + 1;
			return;
		}
	}
	size.x = w;
}

void Cwin::Print() {
	for( int i=0; i<size.y; i++ ){
		for( int j=0; j<size.x; j++ ){
			if( ((j == 0) || (j == size.x - 1)) && (i != 0) )
				mvaddch(pos.y + i, pos.x + j, '|');
			else if( ((i == 0) || (i == size.y - 1)) && ((j != 0) && (j != size.x-1)) )
				mvaddch(pos.y + i, pos.x + j, '_');
			else
				mvaddch(pos.y + i, pos.x + j, ' ');
		}
	}
}

void Cwin::Moveto(struct Pos new_pos) {
	pos = new_pos;
}

void Cwin::Shiftx(int x) {
	pos.x += x;
}

void Cwin::Shifty(int y) {
	pos.y += y;
}

void Cwin::AdjustSize(int h, int w) {
	AdjustWidth(w);
	AdjustHeight(h);
}

int Cwin::Gety() {
	return pos.y;
}

int Cwin::Getx() {
	return pos.x;
}

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
		for( int j=0; j<MAX_TALENTS; j++ ){
			talent_spent[i][j] = 0;
		}
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

void PrintStatNames(struct Pos pos, int* s, int m){
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
		new_pos.y += m;
	}
}

void PrintTalentDiceRoll(PlayerCharacter player, struct Pos pos, int* s){
	int d;
	struct Pos new_pos = pos;
	new_pos.y += 5;
	new_pos.x += 10;
	for( int i=0; i<NUM_STATS; i++ ){
		if( player.GetStat(i) >= 20 )
			d = 5;
		else if( player.GetStat(i) >= 18 )
			d = 4;
		else if( player.GetStat(i) >= 14 )
			d = 3;
		else if( player.GetStat(i) >= 11 )
			d = 2;
		else if( player.GetStat(i) >= 8 )
			d = 1;
		else
			d = 0;

		mvprintw(new_pos.y, new_pos.x, "%s", TALENT_DICE[d].c_str());
		new_pos.y += 1;
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
	mvprintw(pos.y, pos.x + 12, "sp: %i", player.GetStatPoints());
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
		mvprintw(new_pos.y, new_pos.x, "tp: %i", player.GetTalentPoint(i));
		new_pos.y += STAT_MARGIN_Y;
	}
}

void PrintPotentialTalentPoints(PlayerCharacter player, struct Pos pos, int m){
	struct Pos new_pos = pos;
	new_pos.x += 0;
	new_pos.y += 1;
	for( int i=0; i<NUM_STATS; i++ ){
		mvprintw(new_pos.y + 4, new_pos.x + 6, "%i", player.GetPotentialTalentPoint(i));
		new_pos.y += m;
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

void PrintLevelUp(PlayerCharacter player, struct Pos pos, int* s){
	Cwin* cwin = new Cwin(14, 20, pos.y, pos.x);
	Cwin* cwin2 = new Cwin(3, 20, pos.y, pos.x);
	cwin->Print();
	cwin2->Print();
	mvprintw(pos.y + 1, pos.x + 6, "LEVEL UP");
	mvprintw(pos.y + 3, pos.x + 3, "Talent Points:");
	PrintStatNames({pos.y + 5, pos.x + 2}, s, 1);
	PrintTalentDiceRoll(player, pos, s);
}

void PrintStatBuy(PlayerCharacter player, struct Pos pos, int* s){
	Cwin* cwin = new Cwin(14, 20, pos.y, pos.x);
	Cwin* cwin2 = new Cwin(3, 20, pos.y, pos.x);
	cwin->Print();
	cwin2->Print();
	mvprintw(pos.y + 1, pos.x + 6, "BUY STATS");
	mvprintw(pos.y + 4, pos.x + 2, "Stats:");
	mvprintw(pos.y + 4, pos.x + 12, "Cost:");
	PrintStatNames({pos.y + 5, pos.x + 2}, s, 1);
}

void PrintPotentialStats(PlayerCharacter player, struct Pos pos, int m){
	struct Pos new_pos = pos;
	new_pos.x += 0;
	new_pos.y += 1;
	for( int i=0; i<NUM_STATS; i++ ){
		mvprintw(new_pos.y + 4, new_pos.x + 6, "%i", player.GetPotentialStat(i));
		mvprintw(new_pos.y + 4, new_pos.x + 12, "%i", player.GetPotentialStatCost(i));
		new_pos.y += m;
	}
}

void PrintButton(int i, int* s, struct Pos pos, struct Pos size, std::string title){
	int col = 0;
	Cwin* cwin = new Cwin(size.y, size.x, pos.y, pos.x);
	cwin->Print();
	if( s[0] == i ){
		col = 14;
	}
	attron(COLOR_PAIR(col));
	mvprintw(pos.y, pos.x, title.c_str());
	attroff(COLOR_PAIR(col));
}

void PrintTalentSpent(PlayerCharacter player, struct Pos pos, int* s){
	struct Pos new_pos = pos;
	for( int i=0; i<NUM_TALENTS_IN_STAT[s[0]]; i++ ){
		int cost = 1;
		if( player.GetTalentSpent(s, i) >= 14 ){
			cost = 6;
		} else if( player.GetTalentSpent(s, i) >= 10 ){
			cost = 5;
		} else if( player.GetTalentSpent(s, i) >= 8 ){
			cost = 4;
		} else if( player.GetTalentSpent(s, i) >= 5 ){
			cost = 3;
		} else if( player.GetTalentSpent(s, i) >= 3 ){
			cost = 2;
		}

		mvprintw(new_pos.y, new_pos.x, "[%i]", player.GetTalentSpent(s, i));
		mvprintw(new_pos.y, new_pos.x + 22, "%i", cost);
		new_pos.y += 2;
	}
}

void IncrementInt(int& i, int m){
	if( i < m )
		i++;
}

void IncrementIntLoop(int& i, int m){
	if( i == m )
		i = 0;
	else
		i++;
}

void DecrementInt(int& i, int m){
	if( i > m )
		i--;
}

void DecrementIntLoop(int& i, int m){
	if( i == 0 )
		i = m;
	else
		i--;
}

TalentTree* InitTalents(){
	TalentTree* tt = new TalentTree;
	tt->AddTalent(0, "Puglism", "Unarmed damage.");
	tt->AddTalent(0, "Headhunter", "Throwing damage.");
	tt->AddTalent(0, "Warrior", "Weapon damage.");
	tt->AddTalent(0, "Mule", "Carry weight.");
	tt->AddTalent(0, "Way of the Frog", "Jumping increase.");
	tt->AddTalent(0, "Way of the Ram", "Knockback increase.");
	tt->AddTalent(0, "Nutcracker", "Grip strength.");
	tt->AddTalent(1, "Mist", "Chance to dodge.");
	tt->AddTalent(1, "Exploiter", "Chance for subcrit.");
	tt->AddTalent(1, "Accuracy M.", "Chance to Hit (Melee weapons).");
	tt->AddTalent(1, "Accuracy R.", "Chance to Hit (Ranged weapons).");
	tt->AddTalent(1, "Accuracy T.", "Chance to Hit (Thrown weapons).");
	tt->AddTalent(1, "Speedster", "Movement speed increase.");
	tt->AddTalent(1, "Sealegs", "Chance to maintain balance.");
	tt->AddTalent(1, "Featherfall", "Reduced fall damage.");
	tt->AddTalent(1, "Ballistics", "Increase projectile range.");
	tt->AddTalent(1, "Avoidance", "Increased saving throw on AoE effects.");
	tt->AddTalent(2, "Hearty", "Health increase.");
	tt->AddTalent(2, "Healthy", "Resistance increase (Bleeding, Poison, Disease).");
	tt->AddTalent(2, "Aegis", "Chance to deflect damage type.");
	tt->AddTalent(2, "Mouth Breather", "Reduced DoT from neck Constriction.");
	tt->AddTalent(2, "Drunkard", "Drinking tolerance.");
	tt->AddTalent(2, "Poise", "Resistance to knockback.");
	tt->AddTalent(2, "Castle", "Make yourself cover for allies.");
	tt->AddTalent(3, "Empty Mind", "Buff duration increase.");
	tt->AddTalent(3, "Magician", "All spell damage increase.");
	tt->AddTalent(3, "Accuracy S.", "Chance to Hit (Spells).");
	tt->AddTalent(3, "Firebender", "Fire and Lightning damage increase.");
	tt->AddTalent(3, "Ice Maiden", "Ice damage increase.");
	tt->AddTalent(3, "Necromancer", "Necrotic damage increase.");
	tt->AddTalent(3, "The Faithful", "Radiant damage increase.");
	tt->AddTalent(3, "Melting Man", "Acid damage increase.");
	tt->AddTalent(4, "Strong Mind", "Increase DC spell break saves.");
	tt->AddTalent(4, "Watch Your Step!", "Chance to spot traps passively.");
	tt->AddTalent(4, "Show Yourself!", "Chance to spot hidden movements passively.");
	tt->AddTalent(4, "The Doctor", "Increase spell healing.");
	tt->AddTalent(4, "Druidic", "Increased offensive nature damage.");
	tt->AddTalent(4, "Magic Mirror", "Chance to deflect small magic projectiles.");
	tt->AddTalent(4, "Writer's Block", "Chance to gain insight while crafting.");
	tt->AddTalent(5, "Knock Knock,", "Chance to be funny.");
	tt->AddTalent(5, "Who's There?", "Chance to persuade door.");
	tt->AddTalent(5, "Charge!", "Chance for nearby allies to roll +1 initiative.");
	tt->AddTalent(5, "Attack!", "Chance for nearby allies to increase primary damage stat +1.");
	tt->AddTalent(5, "Hold the Line!", "Chance for nearby allies to increase AC +1.");
	tt->AddTalent(5, "Presence", "Increased threat.");
	tt->AddTalent(5, "Distract", "Chance to decrease threat for one turn.");
	tt->AddTalent(5, "Bully", "psychic damage increase.");
	tt->AddTalent(6, "Luck", "Lucky.");
	return tt;
}
