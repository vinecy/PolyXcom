/*
 * Hero.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Vincent
 */

#include"Hero.h"

Hero::Hero(int x,int y,int ID,int pa,int pv,string nom)
{
	Affichable(x,y,ID);
	Personnage(x,y,ID,pa,pv);
	_nom=nom;
}
