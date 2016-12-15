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
#include"Bonus.h"
#include"Armure.h"
using namespace std;

class Inventaire
{
	private:
		list<Arme> 	_inv_weapons;
		list<Bonus>	_inv_bonus;
		list<Armure>_inv_armors;
	public:
		Inventaire();

		list<Arme>		get_weapons();
		list<Bonus>		get_bonus();
		list<Armure>	get_armors();

		~Inventaire();
};



#endif /* INVENTAIRE_H_ */
