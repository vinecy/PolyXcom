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
private:									// ATTRIBUTS
	string _nameFile;							// chemin du fichier en string
	fstream _path;								// fichier
public:
	Fichier(string nameFile, bool readWrite);// CONSTRUCTEURS
											 // METHODES
	void cleanFile(void);						// nettoie le fichier
	void copyFile(string nameFile);				// copie le fichier en argument sur le fichier de référence
	list<string> seekAllNameMap();				// recherche toute les nom de carte dans le fichier

	void loadMap(string nameMap,Carte&,list<Ennemi>&, list<Hero>&, list<Obstacle>&, list<Portail>&); // charge la carte
	void loadSave(string &nameCurrentMap, list<Hero>&, list<Portail>&);								 // charge la sauvegarde
	void loadClosed(list<Portail>&);									// charge la liste des portails dans la sauvegarde
	void updateSave(string nameCurrentMap, list<Hero>&, list<Portail>&);// charge les stats et inventaire de chaque hero dans la sauvegarde

	virtual ~Fichier();								// DESTRUCTEUR
};

#endif /* FICHIER_H_ */
