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
				_graphe[i][j] = new Noeud(i,j,true);
				_graphe[i][j]->set_costFromBegin(-1);
				_graphe[i][j]->set_costFromEnd(-1);
			}
		}
	}

	cout << " + graphe de taille " << _sizeX*_sizeY << " crée" << endl;
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

Noeud Graphe::get_Noeud(int x, int y){
	return *_graphe[x][y];
}

Graphe::~Graphe() {
	int i,j;
	for(i=0 ; i<_sizeX ; i++ ){
		for( j=0 ; j<_sizeY ; j++ ){
			delete _graphe[i][j];
		}
	}
	cout << " + graphe détruit" << endl;
}

