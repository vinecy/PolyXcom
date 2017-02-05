/*
 * Soin.cpp
 *
 *  Created on: 15 déc. 2016
 *      Author: Vincent
 */


/**
 * @file Soin.cpp
 * @brief La classe Soin contient le nombre de medkit et leur efficacite
 *
 */
#include"Soin.h"
#include<iostream>
using namespace std;

/** Constucteur de medkit*/
Soin::Soin()
{
	_uses=1;
	_heal=4;
}

Soin::Soin(int s1, int s2)
{
	_uses=s1;
	_heal=s2;
}

/** change le nombre de medkit disponibles
 * @param q - quantité de medkit a ajouter */

void Soin::add_uses(int q)
{
	_uses=_uses+q;
}

int Soin::get_heal()
{
	return(_heal);
}

void Soin::display_info()
{
	cout<<"Medkit( heal= "<<_heal<<" , uses= "<<_uses<<" )"<<endl;
}

int Soin::get_uses()
{
	return(_uses);
}

/** destructeur de Soin*/
Soin::~Soin()
{

}
