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
	_coordX=0;
	_coordY=0;
	_pvMax=10;
	_paMax=6;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
}

Personnage::Personnage(int x,int y,int pv,int pa)	//construteur surchargé
{
	_coordX=x;
	_coordY=y;
	_pvMax=pv;
	_paMax=pa;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
}

int Personnage::get_x(void)				//getters
{
	return(_coordX);
}
int Personnage::get_y(void)
{
	return(_coordY);
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
void Personnage::set_x(int x)			//setters
{
	_coordX=x;
}
void Personnage::set_y(int y)
{
	_coordY=y;
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
