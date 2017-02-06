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
#include "Noeud.h"					// Il est compose de Noeud
#include "Carte.h"					// Il construit l'arbre à partir de la Carte

class Graphe {
private:										// Attributs
	int _sizeX;											// taille du graphe =
	int _sizeY;											// taille de la carte
public:
	Noeud **_graphe;									// Graphe composé de Noeud

public:
	Graphe(Carte *map);							// CONSTRUCTEUR avec la pointeur sur une carte en argument
												// METHODES
	bool isInTheList(list<Noeud> &l, Noeud &cible);		// Affirme si le Noeud cible est dans la liste l
	list<Noeud> find_Voisin(int xC, int yC);			// Recherche la liste des voisins du noeud (xC,yC)
	void display(void);									// Affiche le graphe

	virtual ~Graphe();							// DESTRUCTEUR
};

#endif /* GRAPHE_H_ */
