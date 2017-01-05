/*
 * Arme.cpp
 *
 *
 *  Created on: 29 nov. 2016
 *      Author: Vincent
 */

/**
 * @file Arme.cpp
 * @brief La classe Arme est la qui contient les informations pour pouvoir faire des degats a distance
 *
 */

#include"Arme.h"
#include <iostream>
using namespace std;

/** Constructeur par defaut de Arme qui construit l'Arme de tier 0*/
Arme::Arme()
{
	_tier=0;
	_degats=3;
	_portee=4;
	_munMax=4;
	_munCurrent=_munMax;//TODO rechargement
}
/** Constructeur de Arme qui cree une arme selon differents parametres
 	 * @param tier - "niveau" de l'arme
 	 * @param degats - degats max de l'arme
 	 * @param portee - portee de l'arme*/
Arme::Arme(int tier,int degats,int portee,int mun)
{
	_tier=tier;
	_degats=degats;
	_portee=portee;
	_munMax=mun;
	_munCurrent=_munMax;
}

int Arme::get_tier(){		//getters
	return(_tier);
}
int Arme::get_degats(){
	return(_degats);
}
int Arme::get_portee(){
	return(_portee);
}
int Arme::get_munCurrent()
{
	return(_munCurrent);
}
int Arme::get_munMax()
{
	return(_munMax);
}

void Arme::set_munCurrent(int i)			//setter
{
	_munCurrent=i;
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
