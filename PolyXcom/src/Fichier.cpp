/*
 * Fichier.cpp
 *
 *  Created on: 12 déc. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include <fstream>			// Utilisation des flux d'entrées sorties de fichiers
#include <cstdlib>
#include "Fichier.h"
#include "Arme.h"


using namespace std;

/** Le constructeur Fichier initialise ouvre le fichier "name".txt
  * pour l'initialisation des niveaux du jeu
	 * @param name - nom du fichier à ouvrir
	 * */
Fichier::Fichier(string name) {
	this->name = name;
	pathCarte = ifstream( "src\\" + name + ".txt");

	cout << " + Creation du fichier " << name << endl;
}

/** La méthode loadSizeMap permet de charger la taille de la carte
 * mis en référence pour l'initialisation des niveaux du jeu
	 * @param &x, &y - nom du fichier à ouvrir
	 * */
void Fichier::loadSizeMap(int &x, int &y){
	int sizeFile;
	string ligne,mot;
	bool notEnd = false;

	if(pathCarte){
		pathCarte.seekg(0, ios::end);
		sizeFile = pathCarte.tellg();
		pathCarte.seekg(0,ios::beg);
		while( (pathCarte.tellg() != sizeFile) && (!notEnd) ){
			pathCarte >> ligne;
			if(ligne == "Taille") notEnd = true ;
		}
		if(notEnd){
			pathCarte >> x;
			pathCarte >> y;
		} else {
			cout << "ERREUR: Atributs \"Taille:\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir " << name << ".txt" << endl;
	}
}

/** La méthode loadMap permet de charger le contenu de la carte
  * mis en référence pour l'initialisation des niveaux du jeu
	 * @param &map - carte à initialisaer
	 * @param &listEnnemi - conteneur de Ennemi à initialiser
	 * @param &listHero - conteneur de Hero à initialiser
	 * @param &listObstacle - conteneur de Obstacle à initialiser
	 * */
void Fichier::loadMap(Carte &map, list<Ennemi> &listEnnemi, list<Hero> &listHero, list<Obstacle> &listObstacle){
	string ligne,mot;
	int sizeFile;

	bool notEnd = false;
	if(pathCarte){
		pathCarte.seekg(0, ios::end);
		sizeFile = pathCarte.tellg();
		pathCarte.seekg(0,ios::beg);

		while( (pathCarte.tellg() != sizeFile) && (!notEnd) ){
			pathCarte >> ligne;
			if(ligne == "Contenu{") notEnd = true ;
		}
		if(notEnd){
			int x,y,ID,lev,str,acc,agi,end,luck;
			string nom;

			pathCarte >> ligne;
			while( ligne != "}"){
				if( ligne == "Ennemi" ){
					pathCarte >> x;
					pathCarte >> y;
					pathCarte >> ID;
					pathCarte >> lev;
					pathCarte >> str;
					pathCarte >> acc;
					pathCarte >> agi;
					pathCarte >> end;
					pathCarte >> luck;
					listEnnemi.push_front(Ennemi(x,y,ID,lev,str,acc,agi,end,luck,Arme()));
					cout << "ceci est un ennemi" << endl;
				} else if( ligne == "Hero" ){
					pathCarte >> x;
					pathCarte >> y;
					pathCarte >> ID;
					pathCarte >> lev;
					pathCarte >> str;
					pathCarte >> acc;
					pathCarte >> agi;
					pathCarte >> end;
					pathCarte >> luck;
					pathCarte >> nom;
					listHero.push_front(Hero(x,y,ID,lev,str,acc,agi,end,luck,Arme(),nom));
					cout << "ceci est un heros" << endl;
				} else if( ligne == "Mur" ){
					pathCarte >> x;
					pathCarte >> y;
					pathCarte >> ID;
					listObstacle.push_front(Obstacle(x,y,ID));
					cout << "ceci est un mur" << endl;
				} else {
					cout << "ERREUR: Element \""<< ligne << "\" inconnu" << endl;
				}
				pathCarte >> ligne;
			}
		} else {
			cout << "ERREUR: Atributs \"Contenu:\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir " << name << ".txt" << endl;
	}
}

/** Le destructeur de Fichier
 * */
Fichier::~Fichier() {
	pathCarte.close();
	cout << " - Destruction du fichier " << name << endl;
}
