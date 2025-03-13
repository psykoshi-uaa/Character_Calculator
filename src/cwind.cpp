#include "../include/cwind.h"
#include <cmath>

Cwind::Cwind()
: rows(0) {
	pos = { 0 };
	size = { 5, 5 };
}

Cwind::Cwind(int h, int w, int r, int y, int x)
: rows(r) {
	pos = { y, x };
	size = { h, w };
}

Cwind::~Cwind(){}


void Cwind::AdjustHeight(int h){
	if( h < 2 ){
		size.y = 2;
		return;
	}
	size.y = h;
}

void Cwind::AdjustWidth(int w){
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


void Cwind::SetTitle(const char* new_title){
	for( int i=0; i<256; i++ ){
		if( new_title[i] != '\0' )
			title[i] = new_title[i];
		else
			return;
	}
}

void Cwind::PrintBorder(){
	for( int i=0; i<size.y; i++ ){
		for( int j=0; j<size.x; j++ ){
			if( (j == 0) || (j == size.x - 1) )
				mvaddch(pos.y + i, pos.x + j, '|');
			else if( (i == 0) || (i == size.y - 1) )
				mvaddch(pos.y + i, pos.x + j, '_');
		}
	}
	mvaddch(pos.y, pos.x, ' ');
	mvaddch(pos.y, size.x, ' ');
}

void Cwind::PrintTitle(){
	int xtitle = 0;
	for( int i=0; i<256; i++ ){
		if( title[i] != '\0' )
			xtitle++;
	}
	xtitle = ceil(size.x/2)-ceil(xtitle/2);
	for( int i=0; i<256; i++ ){
		if( i >= size.x )
			break;
		mvprintw(pos.y+1, pos.x+i+xtitle, "%c", title[i]);
	}
}

void Cwind::Print(){
	PrintBorder();
	PrintTitle();
}

void Cwind::Moveto(int y, int x){
	pos = {y, x};
}

void Cwind::Shiftx(int x){
	pos.x += x;
}

void Cwind::Shifty(int y){
	pos.y += y;
}

void Cwind::AdjustSize(int h, int w){
	AdjustWidth(w);
	AdjustHeight(h);
}

int Cwind::Gety(){
	return pos.y;
}

int Cwind::Getx(){
	return pos.x;
}
