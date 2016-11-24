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

Personnage::Personnage(int pv,int pa)	//construteur surchargé
{
	_pvMax=pv;
	_paMax=pa;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
	_rotation=0;
}



int Personnage::get_pvMax(void)			//getters
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

void Personnage::set_pvMax(int pv)		//setters
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

void Personnage::move_up(Carte map)
{
	if(map.moveIsPossible(_coordX,_coordY+1))
	{
		_coordY++;
		map.update(_coordX,_coordY-1,_coordX,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
void Personnage::move_down(Carte map)
{
	if(map.moveIsPossible(_coordX,_coordY-1))
	{
		_coordY--;
		map.update(_coordX,_coordY+1,_coordX,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
void Personnage::move_left(Carte map)
{
	if(map.moveIsPossible(_coordX-1,_coordY))
	{
		_coordX--;
		map.update(_coordX+1,_coordY,_coordX,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
void Personnage::move_right(Carte map)
{
	if(map.moveIsPossible(_coordX+1,_coordY))
	{
		_coordX++;
		map.update(_coordX-1,_coordY,_coordX,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}

void Personnage::display_info(void)		//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

Personnage::~Personnage()				//destructor
{

}
