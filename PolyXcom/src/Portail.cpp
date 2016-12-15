/*
 * Portail.cpp
 *
 *  Created on: 14 déc. 2016
 *      Author: Valentin BISSUEL
 */

#include "Portail.h"
#include "Affichable.h"

using namespace std;


Portail::Portail(int coordX,int coordY,int ID,int newX,int newY, string nextMap) : Affichable(coordX, coordY, ID){
	_newX = newX ;
	_newY = newY ;
	string _nextNameMap = nextMap ;
}

Portail::~Portail() {
	// TODO Auto-generated destructor stub
}

