/*
 * Obstacle.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Obstacle.h"
#include <iostream>
using namespace std;

/** Le constructeur Affichable construit un Affichable avec initialisation des attributs
	 * @param x - abscisse de l'Obstacle
	 * @param y - Ordonnée de l'Obstacle
	 * @param ID - nombre qui identifie l'Obstacle*/
Obstacle::Obstacle(int x,int y,int ID):Affichable(x,y,ID)
{
	_destrutible=0;
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque la console */
void Obstacle::display_info(void)		//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

/** Le destructeur Obstacle */
Obstacle::~Obstacle()				//destructor
{
	cout << "Obstacle detruit" << endl;
}
