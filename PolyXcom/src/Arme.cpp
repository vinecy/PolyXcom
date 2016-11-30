/*
 * Arme.cpp
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

#include"Arme.h"
#include <iostream>
using namespace std;
/** Constructeur par defaut de Arme qui construit l'Arme de tier 0*/
Arme::Arme()
{
	_tier=0;
	_degats=4;
	_portee=4;
}
/** Constructeur de Arme qui cree une arme selon differents parametres
 	 * @param tier - "niveau" de l'arme
 	 * @param degats - degats max de l'arme
 	 * @param portee - portee de l'arme*/
Arme::Arme(int tier,int degats,int portee)
{
	_tier=tier;
	_degats=degats;
	_portee=portee;
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Arme::display_info(void)
{
	cout<<"Arme(Tier= "<<_tier<<" Degats= "<<_degats<<" Portee= "<<_portee<<")"<<endl;
}

/** Le destructeur Arme*/
Arme::~Arme()
{

}
