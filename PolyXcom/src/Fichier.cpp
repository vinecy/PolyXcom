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
Fichier::Fichier(string nameFile, bool readWrite) {
	_nameFile = nameFile;
	if(readWrite == true){
		_path = fstream( "src\\" + _nameFile + ".txt", ios::in | ios::out);
	} else {
		_path = fstream( "src\\" + _nameFile + ".txt", ios::in );
	}
	cout << " + Creation du fichier " << _nameFile << endl;
}

void Fichier::loadFile(string &nameCurrentMap){
	string mot;
	bool end = 0;
	if(_path){
		_path.seekg(0,ios::beg);
		while( mot != "END" && !end){				// on verifie chaque mot du fichier
			_path >> mot;
			if(mot == "mapCurrent:"){
				_path >> mot;
				nameCurrentMap = mot;
				end = 1;
			}
			//cout << mot << endl;
		}
	} else {
		cout << "ERREUR loadFile: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

void Fichier::cleanFile(void){
	_path.close();
	_path = fstream( "src\\" + _nameFile + ".txt", ios::in | ios::out | ios::trunc);

}
void Fichier::writeFile(string s){
	_path << s << endl;
}

void Fichier::seekMap(list<string> &listNameMap){
	string mot;
	if(_path){
		_path.seekg(0,ios::beg);
		while( mot != "END" ){				// on verifie chaque mot du fichier
			_path >> mot;
			if(mot == "name:"){
				_path >> mot;
				listNameMap.push_back(mot);
			}
			//cout << mot << endl;
		}
	} else {
		cout << "ERREUR seekMap: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

/** La méthode loadSizeMap permet de charger la taille de la carte
 * mis en référence pour l'initialisation des niveaux du jeu
	 * @param nameMap - nom de la carte à initialiser
	 * @param &x, &y - taille à modifier (dimmension x et y)
	 * */
void Fichier::loadSizeMap(string nameMap, int &x, int &y, bool &dZ){
	int sizeFile;
	string ligne;

	// Recherche de la Map en question
	if(_path){
		_path.seekg(0, ios::end);			// Recherche de la taille du fichier
		sizeFile = _path.tellg();
		_path.seekg(0,ios::beg);			// Retour au debut du fichier
		while( (_path.tellg() != sizeFile)	// Tant qu'on n'arrive pas à la fin du fichier
			&& (ligne != nameMap) ){	// et qu'on a pas trouvé la carte suivi de {
			_path >> ligne;					// on verifie chaque mot du fichier
		}
		if(_path.tellg() != sizeFile){		// Si carte trouvé
			while( (ligne != "}")			// Tant qu'on n'arrive pas à }
				&& (ligne != "Taille:") ){  // et qu'on a pas trouvé l'element Taille
				_path >> ligne;				// on continue de chercher
			}
			if(_path.tellg() != sizeFile){  // Si taille trouvé
				_path >> x;
				_path >> y;
				_path >> dZ;
			} else {
				cout << "ERREUR loadSizeMap: Element \"Taille\" non trouvé" << endl;
			}
		} else {
			cout << "ERREUR loadSizeMap: Carte \""<< nameMap <<"\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR loadSizeMap: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

/** La méthode loadMap permet de charger le contenu de la carte
  * mis en référence pour l'initialisation des niveaux du jeu
	 * @param &map - carte à initialisaer
	 * @param &listEnnemi - conteneur de Ennemi à initialiser
	 * @param &listHero - conteneur de Hero à initialiser
	 * @param &listObstacle - conteneur de Obstacle à initialiser
	 * */
void Fichier::loadMap(string nameMap,list<Carte> &listCarte,list<Ennemi> &listEnnemi, list<Hero> &listHero, list<Obstacle> &listObstacle, list<Portail> &listPortail){
	bool dZ;
	string mot;
	list<Ennemi>::iterator ite_e;		//iterateur ennemi
	list<Hero>::iterator ite_h;			//iterateur hero
	list<Obstacle>::iterator ite_o;		//iterateur obstacle

	if(_path){
		_path.seekg(0,ios::beg);			// Retour au debut du fichier
		while( (mot != "END") && (mot != nameMap) ){
			_path >> mot;					// on verifie chaque mot du fichier
		}
		if( mot == (nameMap) ){		// on est bien sur la carte
			int x,y;
			this->loadSizeMap(nameMap, x, y, dZ);
			listCarte.push_back(Carte(nameMap, x , y, dZ));
			while( (mot != "}")	&& (mot != "Contenu{") && (mot != "END") ){
				_path >> mot;
			}
			//cout << mot << endl;
			if(mot == "Contenu{"){			// on est bien dans la partie contenu
				int x,y,ID,lev,str,acc,agi,end,luck;
				string nom;
				_path >> mot;
				//cout << mot << endl;
				while( mot != "}"){
					if( mot == "Ennemi" ){
						_path >> x;
						_path >> y;
						_path >> ID;
						_path >> lev;
						_path >> str;
						_path >> acc;
						_path >> agi;
						_path >> end;
						_path >> luck;
						listEnnemi.push_front(Ennemi(x,y,ID,lev,str,acc,agi,end,luck,Inventaire()));
						cout << "ceci est un ennemi" << endl;
					} else if( mot == "Hero" ){
						_path >> x;
						_path >> y;
						_path >> ID;
						_path >> lev;
						_path >> str;
						_path >> acc;
						_path >> agi;
						_path >> end;
						_path >> luck;
						_path >> nom;
						listHero.push_front(Hero(x,y,ID,lev,str,acc,agi,end,luck,Inventaire(),nom));
						cout << "ceci est un heros" << endl;
					} else if( mot == "Mur" ){
						_path >> x;
						_path >> y;
						_path >> ID;
						listObstacle.push_front(Obstacle(x,y,ID));
						cout << "ceci est un mur" << endl;
					} else {
						cout << "ERREUR loadMap: Element \""<< mot << "\" inconnu" << endl;
					}
					_path >> mot;
				}
			} else {
				cout << "ERREUR loadMap: Atributs \"Contenu{\" non trouvé" << endl;
			}
			/*if(mot == "Portail{"){
				_path >> mot;
				listPortail.push_back(Portail)
			}*/
			list<Carte>::iterator ite_c = listCarte.begin();

			for(ite_e=listEnnemi.begin();ite_e!=listEnnemi.end();ite_e++)	//chargement ennemis
			{
				(*ite_c).addItem((*ite_e));
			}
			for(ite_h=listHero.begin();ite_h!=listHero.end();ite_h++)		//chargement heros
			{
				(*ite_c).addItem((*ite_h));
			}
			for(ite_o=listObstacle.begin();ite_o!=listObstacle.end();ite_o++)	//chargement obstacles
			{
				(*ite_c).addItem((*ite_o));
			}
			//(*ite_c).display();

		} else {
			cout << "ERREUR: Carte \"" << nameMap << "\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

/** Le destructeur de Fichier
 * */
Fichier::~Fichier() {
	_path.close();
	cout << " - Destruction du fichier " << _nameFile << endl;
}
