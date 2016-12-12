/*
 * Noeud.h
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef NOEUD_H_
#define NOEUD_H_

#include <iostream>
using namespace std;

class Noeud {
private:							// Attributs
	int _x;								// Coordonnées x du Noeud
	int _y;								// Coordonnées y du Noeud
protected:
	int _G;								// Cout depuis le noeud de départ
	int _H;								// Cout depuis le noeud d'arrivée
	int _F;								// Sommes des deux couts précedents
public:								// Méthodes
	Noeud();							// Constructeur par défaut
	Noeud(int x, int y);				// Constructeur avec x et y fixés

	void set_costFromBegin(int value);	// Modifie le cout depuis le debut
	void set_costFromEnd(int value);	// Modifie le cout depuis la fin

	int get_costFromBegin(void);		// Retourne le cout depuis le debut
	int get_costFromEnd(void);			// Retourne le cout depuis la fin
	int get_costFinal(void);			// Retourne le cout final
	int get_X(void);					// Retourne X
	int get_Y(void);					// Retourne Y

	void display(ostream &flux) const;	// Méthode pour la redef de <<
	void display();						// Affiche le noeud et ses valeurs

	virtual ~Noeud();					// Le destructeur
};

#endif /* NOEUD_H_ */
