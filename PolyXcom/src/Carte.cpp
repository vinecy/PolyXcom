/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'�l�ves de Polytech Marseille. Il ne peut �tre
 * reproduit, utilis� ou modifi� sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file Carte.cpp
 * @brief La classe Carte permet de g�rer les objets dans le monde
 */

#include <iostream>
#include "Carte.h"
#include "Affichable.h"

using namespace std;

static Affichable vide;


/** Le constructeur Carte initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte
	 * */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_map = new Affichable **[_sizeY];

	// initialisation de la carte
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = &vide;
			_map[i][j] = new Affichable();
		}
	}
	cout << "carte de taille "<< _sizeX << "*" << _sizeY << " cr�e" << endl;
}

/** La m�thode display permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _map[j][i]->get_ID() ;
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
}

/** La m�thode moveIsPossible permet de v�rifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonn�es � verifier
 	 * @return - il retourne 1 et le deplacement est possible ou 0 sinon.
 	 * */
bool Carte::moveIsPossible( int x , int y ){
	return _map[x][y] == &vide ;
}

/** La m�thode addItem permet d'ajouter un affichable sur la carte
 	 * @param &a - adresse de l'affichable � ajouter
 	 * */
void Carte::addItem( Affichable &a ){
	_map[ a.get_x() ][ a.get_y() ] = &a;
}

/** La m�thode moveItemTo permet de deplacer un affichable � un point sur la carte
 	 * @param *a - pointeur sur l'affichable � d�placer sur la carte
 	 * @param newX,newY - nouvelle coordonn�es de l'objet � d�placer
 	 * */
void Carte::moveItemTo( Affichable *a , int newX , int newY ){
	cout << "m�j des coordonnes" << endl;
	int oldX = a->get_x(),
		oldY = a->get_y();
	_map[ newX ][ newY ] = _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = &vide;

	a->set_x(newX);
	a->set_y(newY);
}

/** Le destructeur Carte */
Carte::~Carte() {
	delete _map;

	cout << "carte de taille "<< _sizeX << "*" << _sizeY << " detruit" << endl;
}
