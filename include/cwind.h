#pragma once
#include <curses.h>
#include "lib.h"

#define MAX_WIND_HEIGHT 100

class Cwind {
private:
	struct Vector pos;
	struct Vector size;
	int rows;
	char title[256];
	void AdjustHeight(int h);
	void AdjustWidth(int w);
	
public:
	Cwind();
	Cwind(int h, int w, int r, int y, int x);
	~Cwind();
	void SetTitle(const char* new_title);
	void PrintBorder();
	void PrintTitle();
	void Print();
	void Moveto(int y, int x);
	void Shiftx(int x=0);
	void Shifty(int y=0);
	void AdjustSize(int h, int x);
	int Gety();
	int Getx();
};
