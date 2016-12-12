/*
 * Graphe.h
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef GRAPHE_H_
#define GRAPHE_H_

#include <list>
#include "Noeud.h"
#include "Carte.h"

class Graphe {
private:										// Attributs
	int _sizeX;											// taille du graphe =
	int _sizeY;											// taille de la carte
public:
	Noeud **_graphe;									// Graphe composé de Noeud

												// Constructeurs
public:
	Graphe(Carte *map);									// Constructeur avec la pointeur sur une carte en argument

	bool isInTheList(list<Noeud> &l, Noeud &cible);		// Affirme si le Noeud cible est dans la liste l
	list<Noeud> find_Voisin(int xC, int yC);			// Recherche la liste des voisins du noeud (xC,yC)
	void display(void);									// Affiche le graphe

	virtual ~Graphe();									// Destructeur
};

#endif /* GRAPHE_H_ */
