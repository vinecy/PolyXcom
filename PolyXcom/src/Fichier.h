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
#include "Portail.h"

using namespace std;

class Fichier {
private:											// ATTRIBUTS
	string _nameFile;
	fstream _path;

public:
	Fichier(string nameFile, bool readWrite);		// CONSTRUCTEURS
													// METHODES

	void cleanFile(void);								// nettoie le fichier
	void copyFile(string nameFile);						// copie le fichier en argument sur le fichier de référence

	void loadMap(string nameMap,Carte&,list<Ennemi>&, list<Hero>&, list<Obstacle>&, list<Portail>&);
	void loadSave(string &nameCurrentMap, list<Hero>&, list<Portail>&);
	void updateSave(string &nameCurrentMap, list<Hero>&, list<Portail>&);

	virtual ~Fichier();								// DESTRUCTEUR
};

#endif /* FICHIER_H_ */
