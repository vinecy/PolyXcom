/*
 * Graphe.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include "Graphe.h"
#include "Noeud.h"
#include "Carte.h"
#include <iostream>
#include <list>
using namespace std;

/** Le constructeur Graphe initialise le graphe contenant les noeud pour l'analyse du plus court chemin
	 * @param *map - pointeur sur la carte � analyser
	 * */
Graphe::Graphe(Carte *map) {
	int i = 0,
		j = 0;

	_sizeX = map->get_sizeX();								// La nombre de Noeud du graphe
	_sizeY = map->get_sizeY();								// est �gale � la taille de la carte

	_graphe = new Noeud *[_sizeX];							// Initialisation du graphe selon
	for( i = 0 ; i < _sizeX ; i++ ){						// l'algorithme A*
		_graphe[i] = new Noeud [_sizeY];
		for( j = 0 ; j < _sizeY ; j++ ){
			_graphe[i][j] = Noeud(i,j);
			if( map->moveIsPossible(i, j, false) == false	//Si c'est une case infranchissable
				&& map->get_IDin(i, j) != 0 ){				// c'est � dire un obstacle
				_graphe[i][j].set_costFromBegin(-1);		// on met des couts negatifs �
				_graphe[i][j].set_costFromEnd(-1);			// FromEnd et FromBegin (_G et _H dans le Noeud)
			}
		}
	}
	//cout << " + graphe de taille " << _sizeX*_sizeY << " cr�e" << endl;
}

/** La m�thode isInTheList v�rifie si le Noeud mis en arguments est dans la liste mis en arguments
	 * @param &l - l'adresse de la liste o�  on doit verifier l'existence du noeud
	 * @param &cible - le noeud � verifier
	 * @return - 1 si le noeud est pr�sent et 0 sinon
	 * */
bool Graphe::isInTheList(list<Noeud> &l, Noeud &cible){
	bool rep = false;
	list<Noeud>::iterator lit (l.begin()), lend(l.end());
	while( lit !=lend && rep == false){
		if( (*lit).get_X() == cible.get_X() && (*lit).get_Y() == cible.get_Y() )
			rep = true;
		lit++;
	}
	return (rep);
}

/** La m�thode find_Voisin recherche tout les voisins du noeud de coordon�es xC,yC
	 * @param xC,yC - coordonn�es du noeud concern�
	 * @return - retourne la liste des voisins trouv�s
	 * */
list<Noeud> Graphe::find_Voisin(int xC, int yC){
	list<Noeud> l;												 // Tant qu'on ne sort pas de la carte
	if( xC != _sizeX-1 ) l.push_back(this->_graphe[xC + 1][yC]); // ajout du voisin � droite du Noeud xC,YC
	if( xC != 0 )	     l.push_back(this->_graphe[xC - 1][yC]); // ajout du voisin � gauche du Noeud xC,YC
	if( yC != _sizeY-1 ) l.push_back(this->_graphe[xC][yC + 1]); // ajout du voisin en haut du Noeud xC,YC
	if( yC != 0 ) 		 l.push_back(this->_graphe[xC][yC - 1]); // ajout du voisin en bas du Noeud xC,YC
	return (l);
}

/** La m�thode display affiche le graphe , c'est � dire tout les noeuds ainsi que leur valeur
 * */
void Graphe::display(){
	int i,												// indice parcours sur l'axe Y
		j;												// indice parcours sur l'axe X
	cout << " *** affichage du graphe *** " << endl;
	cout << " ----------------- " << endl;
	for( i = _sizeY-1 ; i >= 0 ; i-- ){
		for( j = 0 ; j < _sizeX ; j++ ){
			cout << " | " << _graphe[j][i].get_costFromBegin() << " ; ";
			cout << _graphe[j][i].get_costFromEnd() << " ; " ;
			cout << _graphe[j][i].get_costFinal();
		}
		cout << " | \n ----------------- " << endl;
	}
	cout << " *** fin affichage *** " << endl;
}


/** Le destructeur de Graphe
 * */
Graphe::~Graphe() {
	//cout << " - graphe d�truit" << endl;
}

