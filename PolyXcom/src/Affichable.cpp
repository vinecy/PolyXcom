/*
 * Affichable.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include "Affichable.h"

Affichable::Affichable(void)
{
	_coordX=0;
	_coordY=0;
	_ID=66;
}

Affichable::Affichable(int x, int y, int ID)
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
}

int Affichable::get_x(void)				//getters
{
	return(_coordX);
}
int Affichable::get_y(void)
{
	return(_coordY);
}

void Affichable::set_x(int x)			//setters
{
	_coordX=x;
}
void Affichable::set_y(int y)
{
	_coordY=y;
}
