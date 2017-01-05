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

/** La m�thode seekAllMap permet de retourner la liste de toutes les cartes du jeu
	 * @param &listNameMap - addrese de la liste des cartes du jeu o� on les stockes
	 * */
void Fichier::seekAllMap(list<string> &listNameMap){
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

/** La m�thode loadSizeMap permet de charger la taille de la carte
 * mis en r�f�rence pour l'initialisation des niveaux du jeu
	 * @param nameMap - nom de la carte � initialiser
	 * @param &x, &y - taille � modifier (dimmension x et y)
	 * */
void Fichier::loadSizeMap(string nameMap, int &x, int &y, bool &dZ){
	int sizeFile;
	string ligne;

	// Recherche de la Map en question
	if(_path){
		_path.seekg(0, ios::end);			// Recherche de la taille du fichier
		sizeFile = _path.tellg();
		_path.seekg(0,ios::beg);			// Retour au debut du fichier
		while( (_path.tellg() != sizeFile)	// Tant qu'on n'arrive pas � la fin du fichier
			&& (ligne != nameMap) ){	// et qu'on a pas trouv� la carte suivi de {
			_path >> ligne;					// on verifie chaque mot du fichier
		}
		cout << "map trouv� :" << ligne;

		if(_path.tellg() != sizeFile){		// Si carte trouv�
			while( (ligne != "}")			// Tant qu'on n'arrive pas � }
				&& (ligne != "Taille:") ){  // et qu'on a pas trouv� l'element Taille
				_path >> ligne;				// on continue de chercher
			}
			cout << "size trouv� :" << ligne;
			if(_path.tellg() != sizeFile){  // Si taille trouv�
				_path >> x;
				_path >> y;
				_path >> dZ;
			} else {
				cout << "ERREUR loadSizeMap: Element \"Taille\" non trouv�" << endl;
			}
		} else {
			cout << "ERREUR loadSizeMap: Carte \""<< nameMap <<"\" non trouv�" << endl;
		}
	} else {
		cout << "ERREUR loadSizeMap: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

/** La m�thode loadMap permet de charger le contenu de la carte
  * mis en r�f�rence pour l'initialisation des niveaux du jeu
  	 * @param nameMap - nom de la map � charger
	 * @param &listCarte - conteneur de carte � initialisaer
	 * @param &listEnnemi - conteneur de Ennemi � initialiser
	 * @param &listHero - conteneur de Hero � initialiser
	 * @param &listObstacle - conteneur de Obstacle � initialiser
	 * */
void Fichier::loadMap(string nameMap,list<Carte> &listCarte,list<Ennemi> &listEnnemi, list<Hero> &listHero, list<Obstacle> &listObstacle, list<Portail> &listPortail){
	bool dZ;
	string mot;
	list<Ennemi>::iterator ite_e;		//iterateur ennemi
	list<Hero>::iterator ite_h;			//iterateur hero
	list<Obstacle>::iterator ite_o;		//iterateur obstacle
	list<Portail>::iterator ite_p;		//iterateur obstacle

	if(_path){
		_path.seekg(0,ios::beg);			// Retour au debut du fichier
		while( (mot != "END") && (mot != nameMap) ){
			while( (mot != "END") && (mot != "name:") ){
				_path >> mot;					// on verifie chaque mot du fichier
			}
			_path >> mot;
		}
		cout << mot << endl;
		if( mot == (nameMap) ){		// on est bien sur la carte
			int x,y;
			// this->loadSizeMap(nameMap, x, y, dZ);
			_path >> mot;
			cout << mot << endl;
			_path >> x;
			_path >> y;
			_path >> dZ;
			listCarte.push_back(Carte(nameMap, x , y, dZ));
			listEnnemi.clear();
			listObstacle.clear();
			listPortail.clear();
			cout << "fin reinitialisation des tanks" << endl;
			_path >> mot;
			if(mot == "Contenu{"){			// on est bien dans la partie contenu
				cout << "recherche du contenu "<< endl;
				int x,y,nX,nY,ID,lev,str,acc,agi,end,luck;
				string nom,nextMap;
				_path >> mot;
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
					} else if( mot == "Portail" ){
						_path >> x;
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
				}									// fin de l'analyse de contenu
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
