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
	 * @param readWrite - booléen indiquant si on ouvre le fichier en lecture/ecriture
	 * ou seulement en écriture
	 * */
Fichier::Fichier(string nameFile, bool readWrite) {
	_nameFile = nameFile;
	if(readWrite == true){														// si mode lecture et ecriture autorisée
		_path = fstream(_nameFile.c_str(), ios::in | ios::out | ios::ate);		// ouverture du fichier en lecture et ecriture
	} else {																	// sinon
		_path = fstream( _nameFile.c_str(), ios::in | ios::ate);				// ouverture du fichier en lecture seule
	}
	cout << " + Creation du fichier " << _nameFile << endl;
}

/** La méthode seekMapCurrent permet de trouver le nom de la carte actuel dans la sauvegarde
	 * @param &nameCurrentMap - adresse du string où on stocke le nom de la carte actuel
	 * */
void Fichier::seekMapCurrent(string &nameCurrentMap){
	string mot;
	bool end = 0;
	if(_path){									// si fichier ouvert
		_path.seekg(0,ios::beg);				// curseur du fichier au début
		while( mot != "END" && !end){			// tant que l'on a pas atteint la fin du fichier et trouvé le champ
			_path >> mot;						// on passe au mot suivant
			if(mot == "mapCurrent:"){			// si on a trouvé le champ
				_path >> mot;					// chargement du nom
				nameCurrentMap = mot;			// dans l'argument par adresse
				end = 1;
			}
		}
	} else {
		cout << "ERREUR loadFile: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

/** La méthode cleanFile permet de reinitialiser le fichier
  * */
void Fichier::cleanFile(void){
	_path.close();
	_path = fstream(_nameFile.c_str(), ios::in | ios::out | ios::trunc);
}

/** La méthode copyFile permet de copier le fichier avec son nom en argument sur le fichier de référence
 	 * @param nameFile - nom du fichier à copier*/
void Fichier::copyFile(string nameFile){
	fstream file = fstream( nameFile.c_str(), ios::in );	// ouverture en lecture seule du fichier de référence
	string ligne;
	if(file){
		cout << "copie du Fichier de sauvegarde par défaut" << endl;
		file.seekg(0,ios::beg);										// curseur fichier de copie au début
		_path.seekg(0,ios::beg);									// curseur fichier de référence au début
		//getline(file, ligne);										// lecteur de la première ligne
		/*while(ligne != "END"){										// tant que l'on attend pas la fin du fichier
			_path << ligne;											// on copie la ligne sur le fichier de référence
			_path << "\n";											// rajout d'un saut de ligne
			getline(file, ligne);									// récupération de la ligne suivante
		}*/
		while(getline(file, ligne)){
			_path << ligne;
			_path << "\n";
		}

		_path << "END";
		file.close();												// fermeture du fichier de copie
		cout << "copie terminée" << endl;
	} else {
		cout << "echec de la copie de " << nameFile << endl;
		exit(EXIT_FAILURE);
	}
}


/** La méthode loadMap permet de charger le contenu de la carte
  * mis en référence pour l'initialisation des niveaux du jeu
  	 * @param nameMap - nom de la map à charger
	 * @param &listCarte - conteneur de carte à initialisaer
	 * @param &listEnnemi - conteneur de Ennemi à initialiser
	 * @param &listHero - conteneur de Hero à initialiser
	 * @param &listObstacle - conteneur de Obstacle à initialiser
	 * */
void Fichier::loadMap(string nameMap,Carte &carteActuel,list<Ennemi> &listEnnemi, list<Hero> &listHero, list<Obstacle> &listObstacle, list<Portail> &listPortail){
	bool dZ;
	string mot;

	if(_path){
		_path.seekg(0,ios::beg);							// Retour au debut du fichier
		while( (mot != "END") && (mot != nameMap) ){		// Curseur du fichier texte sur la ligne
			while( (mot != "END") && (mot != "name:") ){	// où on a le contenu de la carte ayant le
				_path >> mot;								// nom nameMap
			}
			_path >> mot;
		}
		if( mot == (nameMap) ){								// si on est bien sur la carte
			int x,y;										// on récupere la taille
			_path >> mot;									// et le booléen indiquant
			_path >> x;										// si on est dans une zone de danger
			_path >> y;
			_path >> dZ;
			carteActuel = (Carte(nameMap, x , y, dZ));		// création de l'objet Carte correspondant
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
						_path >> x;							// ajout d'un héro
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
				cout << "ERREUR loadMap: Atributs \"Contenu{\" non trouvé" << endl;
			}
		} else {
			cout << "ERREUR: Carte \"" << nameMap << "\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}
}

void Fichier::loadSave(list<Hero>& listHero, list<Portail>&){
	//bool dZ;
	string nameMap,mot;
	string nameHero;
	/*if(_path){
		_path.seekg(0,ios::beg);							// Retour au debut du fichier
		while( (mot != "END") ){		// Curseur du fichier texte sur la ligne
			if(mot == "mapCurrent:"){
				_path >> nameMap;
			} else if( mot == "nameHero:" ){
				_path >> mot;
				while( mot != ";" ) {
					nameHero << mot;
					_path >> mot;
				}
				_path >> mot;
				if( mot == "inventory:"){
					_path >> mot;
					while( mot != ";" ) {
						nameHero << mot;
						_path >> mot;
					}
				}


			} else if( mot == "fellowTravellerName1:"){

			} else if( mot == "fellowTravellerName2:"){

			} else if( mot == "closedPortalList:"){

			} else {
				_path >> mot;
			}
		}



			while( (mot != "END") && (mot != "mapCurrent:") ){	// où on a le contenu de la carte ayant le
				_path >> mot;								// nom nameMap
			}
			_path >> mot;
		}
		if( mot == (nameMap) ){								// si on est bien sur la carte
			int x,y;										// on récupere la taille
			_path >> mot;									// et le booléen indiquant
			_path >> x;										// si on est dans une zone de danger
			_path >> y;
			_path >> dZ;
			carteActuel = (Carte(nameMap, x , y, dZ));		// création de l'objet Carte correspondant
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
						_path >> x;							// ajout d'un héro
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
				cout << "ERREUR loadMap: Atributs \"Contenu{\" non trouvé" << endl;
			}
		} else {
			cout << "ERREUR: Carte \"" << nameMap << "\" non trouvé" << endl;
		}
	} else {
		cout << "ERREUR: Impossible d'ouvrir " << _nameFile << ".txt" << endl;
	}*/
}

/** Le destructeur de Fichier
 * */
Fichier::~Fichier() {
	_path.close();
	cout << " - Destruction du fichier " << _nameFile << endl;
}
