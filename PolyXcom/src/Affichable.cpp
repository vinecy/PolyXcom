/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'élèves de Polytech Marseille. Il ne peut être
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file Affichable.cpp
 * @brief La classe Affichable est la classe mere de tous les objets affichables
 */


#include "Affichable.h"
#include <iostream>
using namespace std;

/** Le constructeur Affichable construit un Affichable par defaut*/
Affichable::Affichable(void)
{
	cout << "Affichable créé" << endl;
	_coordX=0;
	_coordY=0;
	_ID=00;
	cout << "Affichable créé avec les attributs " << _coordX <<  _coordY << _ID << endl;
}

/** Le constructeur Affichable construit un Affichable avec initialisation des attributs
	 * @param x - abscisse de l'Affichable
	 * @param y - Ordonnée de l'Affichable
	 * @param ID - nombre qui identifie l'Affichable*/
Affichable::Affichable(int x, int y, int ID)	//Construteur surchargé
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	cout << "Affichable créé avec les attributs " << _coordX <<  _coordY << _ID << endl;
}

int Affichable::get_x( void )
{
	return (_coordX ) ;
}

int Affichable::get_y(void)
{
	return(_coordY );
}

int Affichable::get_ID(void)
{
	return(_ID );
}

void Affichable::set_x(int x)			//setters
{
	_coordX=x;
}
void Affichable::set_y(int y)
{
	_coordY=y;
}

/** La méthode <b>display_info</b> permet d'afficher les attributs de celui qui l'invoque la console */
void Affichable::display_info(void)		//debug display
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

/** Le destructeur <b>Carte</b> */
Affichable::~Affichable()				//destructeur
{
	cout << "Affichable avec les attributs " << _coordX << " " <<  _coordY << " " << _ID << " detruit " << endl;
}
