/*
 * Graphe.h
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef GRAPHE_H_
#define GRAPHE_H_

#include "Noeud.h"
#include "Carte.h"

class Graphe {
private:
	int _sizeX;
	int _sizeY;
	Noeud ***_graphe;

public:
	Graphe(Carte &map);

	void display(void);

	Noeud get_Noeud(int x, int y);


	virtual ~Graphe();
};

#endif /* GRAPHE_H_ */
