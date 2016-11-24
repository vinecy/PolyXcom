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
 * @todo -
 *
 * @bug -
 */

/**
 * @file Carte.cpp
 * @brief La classe Carte permet de gérer les objets dans le monde
 */

#include <iostream>
#include "Carte.h"

using namespace std;

/** Le constructeur <b>Carte</b> initialise le tableau contenant les objets affichables
	 * @param x - la longueur de la carte
	 * @param y - la largeur de la carte */
Carte::Carte( int x , int y ) {
	_sizeX = x ;
	_sizeY = y ;
	_map = new int*[_sizeY];

	int i,		// indice parcours sur l'axe Y
		j;		// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeY ; i++ ){
		_map[i] = new int[_sizeX];
		for( j = 0 ; j < _sizeX ; j++ ){
			_map[i][j] = 0 ;
		}
	}

	_map[0][0] = 2;
	_map[0][2] = 1;
	_map[0][3] = 3;
	_map[1][0] = 1;
	_map[1][1] = 1;
	_map[2][0] = 3;
}

/** Le destructeur <b>Carte</b> */
Carte::~Carte() {

}

/** La méthode <b>display</b> permet d'afficher la carte sur la console */
void Carte::display( void ) {
	int i;		// indice parcours sur l'axe Y
	cout << " ----------------- " << endl;
	for( i = _sizeX-1 ; i >= 0 ; i-- ){
		cout << " | " << _map[i][0] << " | " << _map[i][1] << " | "<< _map[i][2] << " | "<< _map[i][3] << " | "<< endl;
		cout << " ----------------- " << endl;
	}
}
