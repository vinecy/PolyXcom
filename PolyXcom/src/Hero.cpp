/*
 * Hero.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include<iostream>
#include"Hero.h"
using namespace std;
/** Le constructeur Hero cree un personnage avec un nom
 *	 @param nom - Nom du perso*/
Hero::Hero(string nom)
{
	_nom=nom;
}

/** Le constructeur Hero cree un personnage et initialise ses attributs
	 * @param x - Points de Vie max du perso
	 * @param Y - Points d'Action max du perso
	 * @param ID - Type du hero
	 * @param pv - Points de Vie max du perso
	 * @param pa - Points d'Action max du perso
	 * @param _nom - Nom du perso	*/
Hero::Hero(int x,int y,int ID,int pv, int pa,string nom)
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	_pvMax=pv;
	_pvCurrent=_pvMax;
	_pvMax=pv;
	_paCurrent=_paMax;
	_nom=nom;
}

string Hero::get_name(void)					//getter
{
	return(_nom);
}

void Hero::set_name(string nom)				//setter
{
	_nom=nom;
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Hero::display_info(void)				//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"nom ( "<<this->get_name()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

/** Le destructeur Hero*/
Hero::~Hero()								//destructor
{
	cout << "Hero detruit" << endl;
}
