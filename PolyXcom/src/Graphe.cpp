/*
 * Graphe.cpp
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include "Graphe.h"
#include "Noeud.h"
#include "Carte.h"
#include <iostream>
#include <queue>
using namespace std;

Graphe::Graphe(Carte *map) {
	int i = 0,
		j = 0;

	_sizeX = map->get_sizeX();							// La nombre de Noeud du graphe
	_sizeY = map->get_sizeY();							// est égale à la taille de la carte

	_graphe = new Noeud *[_sizeX];						//
	//cout << " allocation tableau _sizeX...\n";
	for( i = 0 ; i < _sizeX ; i++ ){					// Initialisation du graphe selon
		_graphe[i] = new Noeud [_sizeY];				// l'algorithme A*
		//cout << " allocation tableau _sizeY ...\n";
		for( j = 0 ; j < _sizeY ; j++ ){
			_graphe[i][j] = Noeud(i,j);
			//cout << "adresse Noeud : " << &_graphe[i][j] << "\n";
			if( map->moveIsPossible(i, j) == false 		// Si c'est une case infranchissable
				&& map->get_IDin(i, j) == 1 ){			// c'est à dire un obstacle
				_graphe[i][j].set_costFromBegin(-1);	// on met des couts negatifs à
				_graphe[i][j].set_costFromEnd(-1);		// FromEnd et FromBegin (_G et _H dans le Noeud)
			}
		}
	}
	cout << " + graphe de taille " << _sizeX*_sizeY << " crée" << endl;
}

void Graphe::display(){
	int i,												// indice parcours sur l'axe Y
		j;												// indice parcours sur l'axe X

	cout << " *** affichage du graphe *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _graphe[j][i].get_costFromBegin() << " ; " << _graphe[j][i].get_costFromEnd() << " ; " << _graphe[j][i].get_heuristic();
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
	cout << " *** fin affichage *** " << endl;
}

Noeud Graphe::get_Noeud(int x, int y){
	return _graphe[x][y];
}

Graphe::~Graphe() {
	cout << " - graphe détruit" << endl;
}

