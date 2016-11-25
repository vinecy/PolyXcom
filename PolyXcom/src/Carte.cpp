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
 * @file Carte.cpp
 * @brief La classe Carte permet de gérer les objets dans le monde
 */

#include <iostream>
#include "Carte.h"
#include "Affichable.h"

using namespace std;

/** Le constructeur <b>Carte</b> initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_map = new Affichable **[_sizeY];

	// initialisation de la carte
	int i,		// indice parcours sur l'axe Y
		j;		// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new Affichable*[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = new Affichable();
		}
	}
}

/** La méthode <b>display</b> permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i,		// indice parcours sur l'axe Y
		j;		// indice parcours sur l'axe X

	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _map[j][i]->get_ID() ;
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
}

/** La méthode <b>moveIsPossible</b> permet de vérifier si la case (x,y) est franchissable ou pas
 	 * @param x,y - couple de coordonnées à verifier
 	 * @return - il retourne 1 et le deplacement est possible ou 0 sinon.
 	 * */
bool Carte::moveIsPossible( int x , int y ){
	return (_map[x][y]->get_ID() == 0) ;
}

/** La méthode <b>addItem</b> permet d'ajouter un objet affichable sur la carte
 	 * @param x,y - couple de coordonnées à verifier
 	 * @param a - objet affichable à ajouter
 	 */
void Carte::addItem( Affichable &a){
	*_map[ a.get_x() ][ a.get_y() ] = a;
}

/** La méthode <b>addItem</b> permet d'ajouter un objet affichable sur la carte
 	 * @param oldX,oldY - ancienne coordonnées de l'objet à déplacer
 	 * @param newX,newY - nouvelle coordonnées de l'objet à déplacer
 	 */
void Carte::update( Affichable *a , int newX , int newY ){
	cout << "màj des coordonnes" << endl;
	int oldX = a->get_x(),
		oldY = a->get_y();
	*_map[ newX ][ newY ] = *_map[ oldX ][ oldY ];
	delete _map[ oldX ][ oldY ];
	_map[ oldX ][ oldY ] = new Affichable();
	a->set_x(newX);
	a->set_y(newY);
}

/** Le destructeur <b>Carte</b> */
Carte::~Carte() {
	for( int i = 0 ; i < _sizeX ; i++ ){
		for( int j = 0 ; j < _sizeY ; j++ ){
			delete _map[i][j];
		}
	}
	cout << "Carte detruit" <<  endl;
}
