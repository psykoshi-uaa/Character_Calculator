#include "../include/cwind.h"

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


void Cwind::adjustheight(int h){
	if( h < 2 ){
		size.y = 2;
		return;
	}
	size.y = h;
}

void Cwind::adjustwidth(int w){
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


void Cwind::set_title(const char* new_title){
	for( int i=0; i<256; i++ ){
		if( new_title[i] != '\0' )
			title[i] = new_title[i];
		else
			return;
	}
}

void Cwind::print(){
	int count = 0;
	for( int i=0; i<size.y; i++ ){
		for( int j=0; j<size.x; j++ ){
			if( (i == 0) || (i == size.y - 1) )
				mvaddch(pos.y + i, pos.x + j, '_');
			else if( (j == 0) || (j == size.x - 1) )
				mvaddch(pos.y + i, pos.x + j, '|');
		}
	}
	mvaddch(pos.y, pos.x, ' ');
	mvaddch(pos.y, size.x, ' ');
	mvaddch(size.y, pos.x, '|');
	mvaddch(size.y, size.x, '|');

	for( int i=0; i<256; i++ ){
		if( i >= size.x )
			break;
		mvprintw(pos.y+1, pos.x+i+1+count/2, "%c", title[i]);
	}
}

void Cwind::moveto(int y, int x){
	pos.y = y;
	pos.x = x;
}

void Cwind::shiftx(int x){
	pos.x += x;
}

void Cwind::shifty(int y){
	pos.y += y;
}

void Cwind::adjustsize(int h, int w){
	adjustwidth(w);
	adjustheight(h);
}
