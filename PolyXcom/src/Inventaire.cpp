/*
 * Inventaire.cpp
 *
 *  Created on: 15 d�c. 2016
 *      Author: Vincent
 */

#include "Inventaire.h"
#include"Soin.h"
#include"Grenade.h"

Inventaire::Inventaire()
{
	_inv_weapons.push_front(Arme());
	_inv_armors.push_front(Armure());
	_inv_medkit=Soin();
	_inv_grenade=Grenade();
}

list<Armure> Inventaire::get_armors()
{
	return(_inv_armors);
}

list<Arme> Inventaire::get_weapons()
{
	return(_inv_weapons);
}

Soin Inventaire::get_medkit()
{
	return(_inv_medkit);
}

Grenade Inventaire::get_grenade()
{
	return(_inv_grenade);
}
Inventaire::~Inventaire()
{

}