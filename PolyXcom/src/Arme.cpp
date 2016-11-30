/*
 * Arme.cpp
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

#include"Arme.h"
#include <iostream>
using namespace std;

Arme::Arme()
{
	_tier=0;
	_degats=4;
	_portee=4;
}
Arme::Arme(int tier,int degats,int portee)
{
	_tier=tier;
	_degats=degats;
	_portee=portee;
}

void Arme::display_info(void)
{
	cout<<"Arme(Tier= "<<_tier<<" Degats= "<<_degats<<" Portee= "<<_portee<<")"<<endl;
}


Arme::~Arme()
{

}
