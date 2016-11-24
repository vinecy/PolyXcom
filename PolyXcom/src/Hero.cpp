/*
 * Hero.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include<iostream>
#include"Hero.h"
using namespace std;

Hero::Hero(string nom)				//Constructeur par default
{
	_nom=nom;
}

Hero::Hero(int x,int y,int ID,int pv, int pa,string nom)//construteur surchargé
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	_pvMax=pv;
	_pvCurrent=_pvMax;
	_pvMax=pv;
	_paCurrent=_paMax;
	_nom=nom;
}

string Hero::get_name(void)					//getter
{
	return(_nom);
}

void Hero::set_name(string nom)				//setter
{
	_nom=nom;
}

void Hero::display_info(void)				//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"nom ( "<<this->get_name()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

Hero::~Hero()								//destructor
{

}
