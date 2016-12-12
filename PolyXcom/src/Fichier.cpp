/*
 * Fichier.cpp
 *
 *  Created on: 12 déc. 2016
 *      Author: Valentin BISSUEL
 */

#include "Fichier.h"
#include "Arme.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

Fichier::Fichier(string name) {
	this->name = name;
	pathCarte = ifstream( "src\\" + name + ".txt");

	cout << " + Creation du fichier " << name << endl;
}

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
			int x,y,ID,PV,PA;
			string nom;

			pathCarte >> ligne;
			while( ligne != "}"){
				if( ligne == "Ennemi" ){
					pathCarte >> x;
					pathCarte >> y;
					pathCarte >> ID;
					pathCarte >> PV;
					pathCarte >> PA;
					listEnnemi.push_front(Ennemi(x,y,ID,PV,PA,Arme()));
					cout << "ceci est un ennemi" << endl;
				} else if( ligne == "Hero" ){
					pathCarte >> x;
					pathCarte >> y;
					pathCarte >> ID;
					pathCarte >> PV;
					pathCarte >> PA;
					pathCarte >> nom;
					listHero.push_front(Hero(x,y,ID,PV,PA,Arme(),nom));
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

Fichier::~Fichier() {
	cout << " - Destruction du fichier " << name << endl;
}
