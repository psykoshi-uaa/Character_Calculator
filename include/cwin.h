#pragma once
#include <curses.h>
#include <string>
#include "pos.h"

#define MAX_WIND_HEIGHT 100

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
	void Moveto(int y, int x);
	void Shiftx(int x=0);
	void Shifty(int y=0);
	void AdjustSize(int h, int x);
	int Gety();
	int Getx();
};
