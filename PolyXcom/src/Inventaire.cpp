/*
 * Inventaire.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#include "Inventaire.h"
#include"Soin.h"

Inventaire::Inventaire()
{
	Arme arme = Arme();
	_inv_weapons.push_front(arme);
	Armure arm = Armure();
	_inv_armors.push_front(arm);
	Soin bon = Soin();
	_inv_bonus.push_front(bon);
}

list<Armure> Inventaire::get_armors()
{
	return(_inv_armors);
}

list<Bonus> Inventaire::get_bonus()
{
	return(_inv_bonus);
}

list<Arme> Inventaire::get_weapons()
{
	return(_inv_weapons);
}

Inventaire::~Inventaire()
{

}
