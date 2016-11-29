/*
 * Ennemi.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Ennemi.h"

using namespace std;

/** Le constructeur Ennemi cree un ennemi et initialise ses attributs
	 * @param x - Points de Vie max du perso
	 * @param y - Points d'Action max du perso
	 * * @param ID - Type de l'ennemi
	 * @param pvMax - Points de Vie max du perso
	 * @param paMax - Points d'Action max du perso*/
/*
Ennemi::Ennemi(int pv,int pa)
{
	_pvMax=pv;
	_pvCurrent=_pvMax;
	_pvMax=pv;
	_paCurrent=_paMax;
}
*/
/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Ennemi::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}
/** La méthode begin AI commence l'algorithme de choix de laction par l'AI*/
void Ennemi::begin_IA()
{
	cout<<"begin!"<<endl;
}

/** Le destructeur Ennemi*/
Ennemi::~Ennemi()				//destructor
{
	cout << "Personnage ennemi" << endl;
}

