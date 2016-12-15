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
	_nameNextMap = nextMap ;
	cout << " + portail de " << coordX << "," << coordY << " à "<< _newX << "," << _newY << "dans" << _nameNextMap << " construit" << endl;
}

Portail::~Portail() {
	cout << " - portail de " << _newX << "," << _newY << "dans" << _nameNextMap << " detruit" << endl;
}

