#pragma once
#include <curses.h>
#include "pos.h"
#include "cwin.h"
#include "lib.h"
#include "playercharacter.h"

void PrintStatNames(struct Pos pos, int s);
void PrintStatDescription(struct Pos pos, int stat);
void PrintAvailableTalentPoints(PlayerCharacter player, struct Pos pos);
void PrintCurrentStats(Cwin* statwin, PlayerCharacter player, struct Pos pos, int s);
void PrintCurrentLevel(PlayerCharacter player, struct Pos pos);
void PrintStatTalents(TalentTree* tt, PlayerCharacter player, struct Pos pos, int s, int t);
void PrintStatTalentsDesc(TalentTree* tt, struct Pos pos, int s, int t);
