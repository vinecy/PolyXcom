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

/** La méthode loadSave permet de trouver le nom de la carte actuel dans la sauvegarde
	 * @param &nameCurrentMap - adresse du string où on stocke le nom de la carte actuel
	 * */
void Fichier::loadSave(string &nameCurrentMap, list<Hero>& listHero, list<Portail>& listPortailFerme ){
	string mot;
	int coordSpawnX,coordSpawnY;
	int lev,str,acc,agi,end,luck;
	int s1,s2,g1,g2,g3,a1,a2,a3,a4,ar1,ar2;
	int coordX, coordY, newX, newY;
	list<Arme> la;
	list<Armure> lar;
	Inventaire inv;
	string nom,nextMap;

	if(_path){									// si fichier ouvert
		cout << "chargement sauvegarde " << endl;
		_path.seekg(0,ios::beg);				// curseur du fichier au début
		while( mot != "END"){					// tant que l'on a pas atteint la fin du fichier et trouvé le champ
			_path >> mot;						// on passe au mot suivant
			cout << "1:" << mot << endl;
			if(mot == "mapCurrent:"){			// si on a trouvé le champ "mapCurrent:"
				cout << "carte trouvé" << endl;
				_path >> mot;						// chargement du nom
				nameCurrentMap = mot;				// dans l'argument par adresse
			} else if(mot == "coordSpawn:"){			// si on a trouvé le champ "mapCurrent:"
				cout << "spawn trouvé" << endl;
				_path >> coordSpawnX;
				_path >> coordSpawnY;
			} else if( mot == "nameHero:" || mot == "felowTravellerName1:" || mot == "felowTravellerName2:"){
				cout << "heros trouvé" << endl;
				_path >> mot;
				cout << "2:" << mot << endl;
				nom = "";
				while(mot != ";"){
					nom = nom + mot + " ";
					_path >> mot;
				}
				_path >> mot;
				cout << "3:" << mot << endl;
				if( mot == "inventory:" ){
					cout << "inventaire trouvé" << endl;
					_path >> mot;
					while(mot != ";"){
						if( mot == "Medkit" )
						{
							cout << "Medkit trouvé" << endl;
							_path >> s1;
							_path >> s2;
							_path >> mot;
						} else if( mot == "Grenade")
						{
							_path >> g1;
							_path >> g2;
							_path >> g3;
							_path >> mot;
						} else if( mot == "Arme")
						{
							_path >> a1;
							_path >> a2;
							_path >> a3;
							_path >> a4;
							_path >> mot;
						} else if( mot == "Armure")
						{
							_path >> ar1;
							_path >> ar2;
							_path >> mot;
						}
					}
				}
				_path >> mot;
				cout << "4:" << mot << endl;
				if( mot == "stats:"){			// si on a trouvé le champ "stats:"
					cout << "stats trouvé" << endl;
					_path >> lev;
					_path >> str;
					_path >> acc;
					_path >> agi;
					_path >> end;
					_path >> luck;
					Hero tpsH(coordSpawnX,coordSpawnY,2,lev,str,acc,agi,end,luck,Inventaire(
							Arme(a1,a2,a3,a4),Armure(ar1,ar2),Soin(s1,s2),Grenade(g1,g2,g3),la,lar ),nom);
					listHero.push_back(tpsH);   // creation et ajout du hero dans la liste
					//tpsH.display_info();
				}
			} else if( mot == "closedPortalList "){ // si on a trouvé le champ "closedPortalList:"
				_path >> mot;
				if( mot != ";" ){
					_path >> coordX;
					_path >> coordY;
					_path >> newX;
					_path >> newY;
					_path >> nextMap;
					Portail tpsP(coordX, coordY, 4, newX, newY, nextMap);
					listPortailFerme.push_back(tpsP);	// creation et ajout du portail dans la liste
				}
			} else {
				cout << "ERREUR loadSave: champ " << mot << " inconnu" << endl;
			}
		}

	} else {
		cout << "ERREUR loadSave: Impossible d'ouvrir " << _nameFile << endl;
	}
}

void Fichier::updateSave(string &nameCurrentMap, list<Hero> &listHero, list<Portail> &listPortailFerme){
	//TODO: Urgent

	/*string mot;
	bool trouve = 0;

	int lev,str,acc,agi,end,luck;
	int coordX, coordY, newX, newY;
	Inventaire inv;
	string nom,nextMap;

	if(_path){									// si fichier ouvert
		_path.seekg(0,ios::beg);				// curseur du fichier au début
		while( mot != "END" && !trouve){			// tant que l'on a pas atteint la fin du fichier et trouvé le champ
			_path >> mot;						// on passe au mot suivant
			if(mot == "mapCurrent:"){			// si on a trouvé le champ "mapCurrent:"
				_path >> mot;						// chargement du nom
				nameCurrentMap = mot;				// dans l'argument par adresse
				trouve = 1;
			} else if( mot == "nameHero:"){
				_path >> mot;
				while(mot != ";") nom << mot << " ";
				_path >> mot;
				if( mot == "inventory:" ){
					_path >> mot;
					while(mot != ";"){
						// Definir constructeur de Inventaire
					}
				}
				if( mot == "stats:"){			// si on a trouvé le champ "stats:"
					_path >> lev;
					_path >> str;
					_path >> acc;
					_path >> agi;
					_path >> end;
					_path >> luck;
					Hero tpsH(0,0,2,lev,str,acc,agi,end,luck,Inventaire(),nom);
					listHero.push_back(tpsH);   // creation et ajout du hero dans la liste
				}
			} else if( mot == "closedPortalList:"){ // si on a trouvé le champ "closedPortalList:"
				_path >> coordX;
				_path >> coordY;
				_path >> newX;
				_path >> newY;
				_path >> nextMap;
				Portail tpsP(coordX, coordY, 4, newX, newY, nextMap);
				listPortailFerme.push_back(tpsP);	// creation et ajout du portail dans la liste
			} else {
				cout << "ERREUR loadSave: champ " << mot << " inconnu" << endl;
			}
		}
	} else {
		cout << "ERREUR loadSave: Impossible d'ouvrir " << _nameFile << endl;
	}*/
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
		file.seekg(0,ios::beg);								// curseur fichier de copie au début
		_path.seekg(0,ios::beg);							// curseur fichier de référence au début
		while(getline(file, ligne)){
			_path << ligne;
			_path << "\n";
		}
		_path << "END";
		file.close();										// fermeture du fichier de copie
		cout << "copie terminée" << endl;
	} else {
		cout << "echec de la copie de " << nameFile << endl;
	}
}

list<string> Fichier::seekAllNameMap(){
	list<string> listNameMap;
	string mot;
	if(_path){
		_path.seekg(0,ios::beg);
		_path >> mot;
		while( (mot != "END")){
			if( mot == "name:"){
				_path >> mot;
				listNameMap.push_back(mot);
			} else {
				_path >> mot;
			}

		}
	} else {
		cout << "ERREUR seekAllNameMap: Impossible d'ouvrir " << _nameFile << endl;
	}
	return listNameMap;
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
				cout << "analyse: " <<  mot << endl;
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

/** Le destructeur de Fichier
 * */
Fichier::~Fichier() {
	_path.close();
	cout << " - Destruction du fichier " << _nameFile << endl;
}
