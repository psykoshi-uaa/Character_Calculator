#pragma once
#include <curses.h>
#include "tools.h"

#define MAX_WIND_HEIGHT 100

class Cwind {
private:
	struct Vector pos;
	struct Vector size;
	int rows;
	char title[256];
	void adjustheight(int h);
	void adjustwidth(int w);
	
public:
	Cwind();
	Cwind(int h, int w, int r, int y, int x);
	~Cwind();
	void set_title(const char* new_title);
	void print();
	void moveto(int y, int x);
	void shiftx(int x=0);
	void shifty(int y=0);
	void adjustsize(int h, int x);
};
