/*
 * Fichier.h
 *
 *  Created on: 12 déc. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef FICHIER_H_
#define FICHIER_H_

#include <fstream>			// Utilisation des flux d'entrées sorties de fichiers
#include "Ennemi.h"
#include "Hero.h"
#include "Obstacle.h"
#include "Carte.h"

using namespace std;

class Fichier {
private:
	string name;
	ifstream pathCarte;

public:
	Fichier(string name);

	void loadMap(Carte&, list<Ennemi>&, list<Hero>&, list<Obstacle>&);
	void loadSizeMap(int&,int&);

	virtual ~Fichier();
};

#endif /* FICHIER_H_ */
