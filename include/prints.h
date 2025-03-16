#pragma once
#include <curses.h>
#include "pos.h"
#include "cwin.h"
#include "lib.h"
#include "playercharacter.h"

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
void PrintHelp(struct Pos pos, int w);
