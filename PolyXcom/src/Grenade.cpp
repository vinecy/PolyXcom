/*
 * Grenade.cpp
 *
 *  Created on: 15 d�c. 2016
 *      Author: Vincent
 */

#include"Grenade.h"
#include<iostream>
using namespace std;

/** Le constructeur de Grenade cree un nombre de grenade, leur portee et les degats associes*/
Grenade::Grenade()
{
	_range=1;
	_number=0;
	_dammage=4;
}

/** la fonction add_number sert a ajuster le nombre de grenades disponible
 * @param q - quantit� a ajouter ou retirer de grenade*/
void Grenade::add_number(int q)
{
	cout << _number << endl;
	_number=_number+q;//TODO NON FCT
	cout << _number << endl;
}

int Grenade::get_dammage()
{
	return(_dammage);
}

int Grenade::get_number()
{
	return(_number);
}

/** La m�thode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Grenade::display_info()
{
	cout<<"Grenade( damage= "<<_dammage<<" , range= "<<_range<<" , number= "<<_number<<" )"<<endl;
}

/** destructeur de Grenade*/
Grenade::~Grenade()
{

}
