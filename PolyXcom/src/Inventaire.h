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
		list<Arme>	_inv_weapons;
		list<Armure>_inv_armors;
		Soin		_inv_medkit;
		Grenade		_inv_grenade;
	public:
		Inventaire();

		list<Arme>	get_weapons();
		list<Armure>get_armors();
		Soin		get_medkit();
		Grenade		get_grenade();

		~Inventaire();
};



#endif /* INVENTAIRE_H_ */
