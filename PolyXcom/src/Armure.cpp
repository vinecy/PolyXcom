/*
 * Armure.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */

#include"Armure.h"
#include<iostream>
using namespace std;

/** constructeur par defaut d armure */
Armure::Armure()
{
	_tier=0;
	_protection=1;
}

/** constructeur  d armure
 * @param tier - nombre representatif du niveau de l armure*/
Armure::Armure(int tier)
{
	_tier=tier;
	_protection=2*tier;
}


/** constructeur  d armure
 * @param tier - nombre representatif du niveau de l armure
 * @param prot - nombre de degat protege par l armure*/
Armure::Armure(int tier,int prot)
{
	_tier=tier;
	_protection=prot;
}

int Armure::get_protection()
{
	return(_protection);
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque la console */
void Armure::display_info()
{
	cout<<"Armure ( Tier= "<<_tier<<" , protection= "<<_protection<<" )"<<endl;
}

/** destucteur d armure*/
Armure::~Armure()
{

}


