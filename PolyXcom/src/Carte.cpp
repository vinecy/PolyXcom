/*
 * Carte.cpp
 *
 *  Created on: 24 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include "Carte.h"

using namespace std;

// COMMENTAIRE
Carte::Carte() {
	sizeX = 4 ;
	sizeY = 4 ;
	map = new int*[sizeY];

	int i,		// indice parcours sur l'axe Y
		j;		// indice parcours sur l'axe X
	for( i = 0 ; i < sizeY ; i++ ){
		map[i] = new int[sizeX];
		for( j = 0 ; j < sizeX ; j++ ){
			map[i][j] = 0 ;
		}
	}
	map[0][0] = 2;
	map[0][2] = 1;
	map[0][3] = 3;
	map[1][0] = 1;
	map[1][1] = 1;
	map[2][0] = 3;
}

// COMMENTAIRE
Carte::~Carte() {

}

void Carte::display() {
	int i;		// indice parcours sur l'axe Y
	cout << "  ------------------  " << endl;
	for( i = 0 ; i < sizeX ; i++ ){
		cout << " | " << map[i][0] << " | " << map[i][1] << " | "<< map[i][2] << " | "<< map[i][3] << " | "<< endl;
		cout << "  ------------------  " << endl;
	}
}
