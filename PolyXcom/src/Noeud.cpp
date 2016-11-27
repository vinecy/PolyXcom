/*
 * Noeud.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include "Noeud.h"

using namespace std;

Noeud::Noeud(int x, int y, bool isObstacle) {
	_x = x;
	_y = y;
	_costFromBegin = 0;
	_costFromEnd = 0;
	_heuristic = 0 ;
	_isObstacle = isObstacle;
	cout << " + noeud " << _x << "," << _y << " créé " << endl;
}

Noeud::Noeud(int x, int y, bool isObstacle, int F, int G, int H){
	_x = x;
	_y = y;
	_costFromBegin = F;
	_costFromEnd = G;
	_heuristic = H ;
	_isObstacle = isObstacle;
	cout << " + noeud créé " << endl;
}

void Noeud::set_costFromBegin(int value){
	_costFromBegin = value;
}

void Noeud::set_costFromEnd(int value){
	_costFromEnd = value;
}

void Noeud::set_heuristic(int value){
	_heuristic = value;
}

int Noeud::get_costFromBegin(void){
	return _costFromBegin;
}

int Noeud::get_costFromEnd(void){
	return _costFromEnd;
}

int Noeud::get_heuristic(void){
	return _heuristic;
}



Noeud::~Noeud() {
	cout << " - noeud détruit " << endl;
}

