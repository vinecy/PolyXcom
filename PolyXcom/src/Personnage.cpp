/*
 * Personnage.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include "Personnage.h"
#include <iostream>

using namespace std;

Personnage::Personnage()		//constructeur par defaut
{
	_pvMax=10;
	_paMax=6;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
	_rotation=0;
}

Personnage::Personnage(int x,int y,int ID,int pv,int pa)	//construteur surchargé
{
	Affichable(x,y,ID);
	_pvMax=pv;
	_paMax=pa;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
	_rotation=0;
}



int Personnage::get_pvMax(void)
{
	return(_pvMax);
}
int Personnage::get_paMax(void)
{
	return(_paMax);
}
int Personnage::get_pvCurrent(void)
{
	return(_pvCurrent);
}
int Personnage::get_paCurrent(void)
{
	return(_paCurrent);
}

void Personnage::set_pvMax(int pv)
{
	_pvMax=pv;
}
void Personnage::set_paMAx(int pa)
{
	_paMax=pa;
}
void Personnage::set_pvCurrent(int pv)
{
	_pvCurrent=pv;
}
void Personnage::set_paCurrent(int pa)
{
	_paCurrent=pa;
}

void Personnage::display_info(void)		//debug display
{
	cout<<"///////BEGIN DEBUG DISPLAY/////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"/////// END DEBUG DISPLAY/////"<<endl;
}
Personnage::~Personnage()
{

}
