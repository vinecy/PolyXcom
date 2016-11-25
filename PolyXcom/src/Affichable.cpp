/*
 * Affichable.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include "Affichable.h"
#include <iostream>
using namespace std;

Affichable::Affichable(void)			//Construteur par defaut
{
	cout << "Affichable créé" << endl;
	_coordX=0;
	_coordY=0;
	_ID=00;
}

Affichable::Affichable(int x, int y, int ID)	//Construteur surchargé
{

	_coordX=x;
	_coordY=y;
	_ID=ID;
	cout << "Affichable créé avec les attributs " << _coordX <<  _coordY << _ID << endl;
}

int Affichable::get_x(void)				//getters
{
	return(_coordX);
}
int Affichable::get_y(void)
{
	return(_coordY);
}
int Affichable::get_ID(void)
{
	return(_ID);
}

void Affichable::set_x(int x)			//setters
{
	_coordX=x;
}
void Affichable::set_y(int y)
{
	_coordY=y;
}


void Affichable::display_info(void)		//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

Affichable::~Affichable()				//destructeur
{
	cout << "Affichable à l'ID " << _ID << " aux cordonnees ( " << _coordX << "," << _coordY << " ) detruit" << endl;
}
