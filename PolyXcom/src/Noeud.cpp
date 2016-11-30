/*
 * Noeud.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include "Noeud.h"

using namespace std;

Noeud::Noeud(){
	_x = 0;
	_y = 0;
	_G = 0;
	_H = 0;
	_F = _G + _H;
	cout << " + noeud cr�� " << endl;
}

Noeud::Noeud(int x, int y) {
	_x = x;
	_y = y;
	_G = 0;
	_H = 0;
	_F = _G + _H;
	cout << " + noeud " << _x << "," << _y << " cr�� " << endl;
}

bool Noeud::sameCoord(Noeud const&a){
	return( this->_x == a._x && this->_y == a._y );
}


void Noeud::set_costFromBegin(int value){
	_G = value;
	_F = _G + _H;
}

void Noeud::set_costFromEnd(int value){
	_H = value;
	_F = _G + _H;
}

int Noeud::get_costFromBegin(void){
	return _G;
}

int Noeud::get_costFromEnd(void){
	return _H;
}

int Noeud::get_heuristic(void){
	return _F;
}

int Noeud::get_X(void){
	return _x;
}

int Noeud::get_Y(void){
	return _y;
}

Noeud::~Noeud() {
	cout << " - noeud " << _x << "," <<  _y << " d�truit " << endl;
}
