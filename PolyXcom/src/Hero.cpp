/*
 * Hero.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include<iostream>
#include"Hero.h"
using namespace std;

Hero::Hero(string nom)
{
	_nom=nom;
}

string Hero::get_name(void)
{
	return(_nom);
}

void Hero::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"nom ( "<<this->get_name()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

Hero::~Hero()
{

}
