#include <cmath>
#include <string>
#include "../include/cwin.h"

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
