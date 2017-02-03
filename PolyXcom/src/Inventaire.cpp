/*
 * Inventaire.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

/**
 * @file Inventaire.cpp
 * @brief La classe Inventaire regroupe arme, armure, medkit et grenade du personnage
 *
 */

#include"Inventaire.h"
#include"Soin.h"
#include"Grenade.h"

/** Le constructeur Inventaire construit un Inventaire avec initialisation des attributs*/
Inventaire::Inventaire()
{
	_inv_armor_c=Armure();
	_inv_weapon_c=Arme();
	_inv_weapons.push_front(Arme());
	_inv_armors.push_front(Armure());
	_inv_medkit=Soin();
	_inv_grenade=Grenade();
}

Inventaire::Inventaire(Arme arme,Armure armure,Soin soin,Grenade gre,list<Arme> la,list<Armure> lar)
{
	_inv_armor_c=armure;
	_inv_weapon_c=arme;
	_inv_weapons=la;
	_inv_armors=lar;
	_inv_medkit=soin;
	_inv_grenade=gre;
}


list<Armure> Inventaire::get_armors()
{
	return(_inv_armors);
}

list<Arme> Inventaire::get_weapons()
{
	return(_inv_weapons);
}

Arme* Inventaire::get_weapon_c()
{
	return(&_inv_weapon_c);
}

Armure* Inventaire::get_armor_c()
{
	return(&_inv_armor_c);
}

Soin* Inventaire::get_medkit()
{
	return(&_inv_medkit);
}

Grenade* Inventaire::get_grenade()
{
	return(&(_inv_grenade));
}

/**Destucteur Inventaire*/
Inventaire::~Inventaire()
{

}
