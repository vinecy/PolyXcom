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
using namespace std;

Graphe::Graphe(Carte &map) {
	int i = 0,
		j = 0;

	_sizeX = map.get_sizeX();
	_sizeY = map.get_sizeY();

	_graphe = new Noeud **[_sizeX];
														// indice parcours sur l'axe X
	for( i = 0 ; i < _sizeX ; i++ ){
		_graphe[i] = new Noeud *[_sizeY];
		for( j = 0 ; j < _sizeY ; j++ ){
			if( map.get_IDin(i, j) != 1 ){
				_graphe[i][j] = new Noeud(i,j,false);
			} else {
				_graphe[i][j] = new Noeud(i,j,true,-1,-1,-1);
			}
		}
	}

	cout << " + graphe de taille " << _sizeX*_sizeY << " crée" << endl;
}

void Graphe::pathfinding( int xA, int xB, int yA, int yB ){
	Noeud *depart = _graphe[xA][yA];
	Noeud *arrivee= _graphe[xB][yB];




}




void Graphe::display(){
	int i,														// indice parcours sur l'axe Y
		j;														// indice parcours sur l'axe X

	cout << " *** affichage du graphe *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _graphe[j][i]->get_costFromBegin() << " ; " << _graphe[j][i]->get_costFromEnd() << " ; " << _graphe[j][i]->get_heuristic();
		}
		cout << " | "<< endl << " ----------------- " << endl;
	}
	cout << " *** fin affichage *** " << endl;
}

Graphe::~Graphe() {
	delete _graphe;
	cout << " + graphe détruit" << endl;
}

