/*
 * Fichier.h
 *
 *  Created on: 12 d�c. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef FICHIER_H_
#define FICHIER_H_

#include <fstream>			// Utilisation des flux d'entr�es sorties de fichiers
#include "Ennemi.h"
#include "Hero.h"
#include "Obstacle.h"
#include "Carte.h"
#include "Portail.h"

using namespace std;

class Fichier {
private:
	string _nameFile;
	fstream _path;

public:
	Fichier(string nameFile, bool readWrite);

	void seekMapCurrent(string &nameCurrentMap);
	void cleanFile(void);
	void writeFile(string s);

	void seekAllMap(list<string>&);
	void loadMap(string nameMap,list<Carte>&,list<Ennemi>&, list<Hero>&, list<Obstacle>&, list<Portail>&);
	void loadSizeMap(string nameMap,int&,int&,bool&);

	virtual ~Fichier();
};

#endif /* FICHIER_H_ */
