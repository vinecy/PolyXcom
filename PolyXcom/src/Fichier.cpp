/*
 * Fichier.cpp
 *
 *  Created on: 12 d�c. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include <fstream>			// Utilisation des flux d'entr�es sorties de fichiers
#include <cstdlib>
#include "Fichier.h"
#include "Arme.h"


using namespace std;

/** Le constructeur Fichier initialise ouvre le fichier "name".txt
  * pour l'initialisation des niveaux du jeu
	 * @param name - nom du fichier � ouvrir
	 * @param readWrite - bool�en indiquant si on ouvre le fichier en lecture/ecriture
	 * ou seulement en �criture
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

/** La m�thode seekMapCurrent permet de trouver le nom de la carte actuel dans la sauvegarde
	 * @param &nameCurrentMap - adresse du string o� on stocke le nom de la carte actuel
	 * */
void Fichier::seekMapCurrent(string &nameCurrentMap){
	string mot;
	bool end = 0;
	if(_path){
		_path.seekg(0,ios::beg);
		while( mot != "END" && !end){
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

/** La m�thode cleanFile permet de reinitialiser le fichier
  * */
void Fichier::cleanFile(void){
	_path.close();
	_path = fstream( "src\\" + _nameFile + ".txt", ios::in | ios::out | ios::trunc);
}

/** La m�thode writeFile permet d'�crire une chaine de caract�re dans le fichier
 	 * @param s - la chaine de caract�re � �crire dans le fichier*/
void Fichier::writeFile(string s){
	_path << s << endl;
}

/** La m�thode loadMap permet de charger le contenu de la carte
  * mis en r�f�rence pour l'initialisation des niveaux du jeu
  	 * @param nameMap - nom de la map � charger
	 * @param &listCarte - conteneur de carte � initialisaer
	 * @param &listEnnemi - conteneur de Ennemi � initialiser
	 * @param &listHero - conteneur de Hero � initialiser
	 * @param &listObstacle - conteneur de Obstacle � initialiser
	 * */
void Fichier::loadMap(string nameMap,Carte &carteActuel,list<Ennemi> &listEnnemi, list<Hero> &listHero, list<Obstacle> &listObstacle, list<Portail> &listPortail){
	bool dZ;
	string mot;

	if(_path){
		_path.seekg(0,ios::beg);							// Retour au debut du fichier
		while( (mot != "END") && (mot != nameMap) ){		// Curseur du fichier texte sur la ligne
			while( (mot != "END") && (mot != "name:") ){	// o� on a le contenu de la carte ayant le
				_path >> mot;								// nom nameMap
			}
			_path >> mot;
		}
		if( mot == (nameMap) ){								// si on est bien sur la carte
			int x,y;										// on r�cupere la taille
			_path >> mot;									// et le bool�en indiquant
			_path >> x;										// si on est dans une zone de danger
			_path >> y;
			_path >> dZ;
			carteActuel = (Carte(nameMap, x , y, dZ));		// cr�ation de l'objet Carte correspondant
			listEnnemi.clear();								// init du conteneur d'ennemi
			listObstacle.clear();							// init du conteneur d'obstacle
			listPortail.clear();							// init du conteneur de Portail
			_path >> mot;
			if(mot == "Contenu{"){							// si on est bien dans la partie contenu
				cout << "recherche du contenu "<< endl;		// rajout du contenu dans les conteneurs
				int x,y,nX,nY,ID,lev,str,acc,agi,end,luck;
				string nom,nextMap;
				_path >> mot;
				while( mot != "}"){
					if( mot == "Ennemi" ){
						_path >> x;							// ajout d'un ennemi
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
						_path >> x;							// ajout d'un h�ro
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
						_path >> x;							// ajout d'un obstacle
						_path >> y;
						_path >> ID;
						listObstacle.push_front(Obstacle(x,y,ID));
						cout << "ceci est un mur" << endl;
					} else if( mot == "Portail" ){
						_path >> x;							// ajout d'un portail
						_path >> y;
						_path >> ID;
						_path >> nX;
						_path >> nY;
						_path >> nextMap;
						listPortail.push_front(Portail(x,y,ID,nX,nY,nextMap));
						cout << "ceci est un portail" << endl;
					} else {
						cout << "ERREUR loadMap: Element \""<< mot << "\" inconnu" << endl;
					}
					_path >> mot;
				}											// fin de l'analyse de contenu
				cout << "fin de l'analyse" << endl;
			} else {
				cout << "ERREUR loadMap: Atributs \"Contenu{\" non trouv�" << endl;
			}
		} else {
			cout << "ERREUR: Carte \"" << nameMap << "\" non trouv�" << endl;
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
