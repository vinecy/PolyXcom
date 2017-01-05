/*
 * Inventaire.h
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#ifndef INVENTAIRE_H_
#define INVENTAIRE_H_

#include<list>
#include"Arme.h"
#include"Soin.h"
#include"Grenade.h"
#include"Armure.h"
using namespace std;

class Inventaire
{
	private:
		list<Arme>	_inv_weapons;		//liste d'arme possedee par le personnage
		list<Armure>_inv_armors;		//liste d'armure possedee par le personnage
		Soin		_inv_medkit;		//medkit possedes par le personnage
		Grenade		_inv_grenade;		//grenades possedees par le personnage

	public:
		Inventaire();					//constructeur

		list<Arme>	get_weapons();		//getters
		list<Armure>get_armors();
		Soin		get_medkit();
		Grenade		get_grenade();

		~Inventaire();					//destructeur
};



#endif /* INVENTAIRE_H_ */
