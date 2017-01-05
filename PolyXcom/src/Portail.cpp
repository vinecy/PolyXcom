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

int Portail::get_newX( void ){
	return _newX;
}

int Portail::get_newY( void ){
	return _newY;
}

string Portail::get_nameNextMap( void ){
	return _nameNextMap;
}

void Portail::display( void ){
	cout << "portail sur " << _nameNextMap << " au coord " << _newX << "," << _newY << endl;
}

Portail::~Portail() {
	cout << " - portail de " << _newX << "," << _newY << "dans" << _nameNextMap << " detruit" << endl;
}

