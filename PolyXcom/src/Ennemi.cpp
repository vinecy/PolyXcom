/*
 * Ennemi.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Ennemi.h"

using namespace std;

Ennemi::Ennemi(int x,int y,int ID,int pv,int pa)
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	_pvMax=pv;
	_pvCurrent=_pvMax;
	_pvMax=pv;
	_paCurrent=_paMax;
}

void Ennemi::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

void Ennemi::begin_IA()
{
	cout<<"begin!"<<endl;
}

/** Le destructeur Ennemi*/
Ennemi::~Ennemi()				//destructor
{
	cout << "Personnage ennemi" << endl;
}

