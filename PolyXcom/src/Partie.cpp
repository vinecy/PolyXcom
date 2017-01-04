/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'élèves de Polytech Marseille. Il ne peut être
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 */

/**
 * @author BARTHOLOMEAU Vincent <vincent.bartholomeau@etu.univ-amu.fr>
 * @author BISSUEL Valentin <valentin.bissuel@etu.univ-amu.fr>
 *
 * @version 0.0.1 / 24/11/2016
 *
 */

/**
 * @file Partie.cpp
 * @brief La classe Partie permet de gérer la partie du joueur, la gestion des item, des cartes,
 * des ennemis, des heros, etc.
 */

#include "Partie.h"
#include "Fichier.h"

using namespace std;

/** Le constructeur Partie crée la partie en cours
  * */
Partie::Partie() {
	cout << " + Partie construite " << endl;
}

/** La méthode newPartie permet d'initialiser le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::newPartie(void){
	Fichier pathFile("Save",1); 				// ouverture en lecture et ecriture de la sauvegarde
	pathFile.cleanFile();						// init de la sauvegarde
	pathFile.writeFile("mapCurrent: Luminy");	// réecriture du fichier initiale
	//TODO faire une copie du fichier de référence pour l'init d'une sauvegarde

}

/** La méthode loadPartie permet de charger le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::loadPartie(void){
	Fichier pathMap("World",0); 	// ouverture en lecture de la carte
	Fichier pathFile("Save",1); 	// ouverture en lecture et ecriture de la sauvegarde
	list<Ennemi>::iterator ite_e;	// itérateur d'ennemi
	list<Hero>::iterator   ite_h;	// itérateur de héros
	string nameCurrentMap;			// nom de la carte actuel

	pathFile.seekMapCurrent(nameCurrentMap);// recherche de la carte actuel dans la sauvegarde
	pathMap.seekAllMap(_collec_carte);		// recherche de toutes les autres cartes
	// chargement de la carte actuel
	pathMap.loadMap(nameCurrentMap, _tank_carte, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	// itérateur sur la carte actuel
	_ite_c = _tank_carte.begin();
	while( ( (*_ite_c).get_nameMap() != nameCurrentMap )
		&& ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		(*_ite_c).addItem((*_ite_e));
	}
	// ajout des héros sur la carte
	for(_ite_h = _tank_hero.begin();_ite_h!=_tank_hero.end();_ite_h++){
		(*_ite_c).addItem((*_ite_h));
	}
	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		(*_ite_c).addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		(*_ite_c).addItem((*_ite_p));
	}
	// initialisation de la team d'ennemis sur la carte actuel
	for(ite_e = _tank_ennemi.begin() ; ite_e != _tank_ennemi.end() ; ite_e++){
		_team_ennemi.push_front( &(*ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	for(ite_h = _tank_hero.begin() ; ite_h != _tank_hero.end() ; ite_h++){
		_team_hero.push_front( &(*ite_h) );
	}
}

/** La méthode launchPartie permet de lancer le jeu en fonction de la sauvegarde
  * */
void Partie::launchPartie(void){
	bool exitGame = 0,									// boolean indiquant si on quitte le jeu
		 isDangerZone = (*_ite_c).get_dangerZone();		// boolean indiquant si on est en zone de combat ou non
	while(!exitGame){
		if( isDangerZone == true ){ 					// mode Combat
			cout << " Alerte! Ennemi en vue! " << endl;
			this->fightMode();
			isDangerZone = false;
			cout << "gain de niveau " << endl;
		} else {										// mode Exploration
			cout << " RAS " << endl;
			this->explorationMode();
			isDangerZone = true;
		}
		//exitGame = true;
	}
}
// TODO
void Partie::savePartie(void){

}
// TODO
void Partie::switchMap( int x , int y , string nextMap ){
	Fichier pathMap("World",0);
	//list<Hero> tank_hero;
	//list<Hero>::iterator ite_h;

	pathMap.loadMap(nextMap, _tank_carte, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	// recherche de la Map
	_ite_c = _tank_carte.begin();
	while( ( (*_ite_c).get_nameMap() != nextMap ) && ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}

	//TODO trouver algorithme qui place les héros sur la map vers le portail



	/*// maj de la coord du héro
	_ite_h = _tank_hero.begin();
	(*_ite_h).set_x(x); (*_ite_h).set_y(y);


	for( _ite_h = _tank_hero.begin(); _ite_h != _tank_hero.end(); _ite_h++ ){
		tank_hero.push_front(*_ite_h);
		_tank_hero.pop_front();
	}
	pathMap.loadMap(nextMap, _tank_carte, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	ite_h = tank_hero.begin();
	ite_h++;


	for( ; ite_h != tank_hero.end(); ite_h++ ){

		(*ite_h).set_x(x);
		(*ite_h).set_y(y);
		_tank_hero.push_back(*ite_h);
	}*/
}

/** La méthode explorationMode définit le mode exploration du jeu
  * */
void Partie::explorationMode(void){
	cout << " Mode exploration " << endl;
	bool endGame = false,					// booléen indiquant la fin du jeu
		 acrossNewMap = 0;					// booléen indiquant si on franchit une nouvelle carte
	//int heroX,heroY;						// coordonnées du héro

	while(!acrossNewMap && !endGame){
		_ite_l = _team_hero.begin();		// itérateur sur le héros principal
		(*_ite_c).display();				// affichage de la carte
		endGame = this->move_choice(0);				// choix du mouvement à faire
		/*


		// TODO les compagnons suivent le héros principal
		heroX = (*_ite_l)->get_x();
		heroY = (*_ite_l)->get_y();
		_ite_l++; 							// c'est un compagnon à partir du deuxième élément de la liste
		while(_ite_l != _team_hero.end()){
			(*_ite_c).moveItemToWithMoveAnim( (*_ite_l)->get_x(), (*_ite_l)->get_y(), heroX, heroY);
			_ite_l++;						// heros suivant
		}*/
	}
}

/** La méthode fightMode définit le mode combat du jeu
  * */
void Partie::fightMode(void){
	bool endFight = 0;						// booléen qui indique si c'est la fin du combat
	cout << " Mode Combat " << endl;

	while(!endFight){
		cout << "\t\t\t\t\t\t\t\tNouveau tour"<<endl;
		_ite_l = _team_hero.begin();
		while(end_team(_team_hero)){
			this->allieTour(endFight);
		}
		for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){
			(*_ite)->set_paCurrent((*_ite)->get_paMax());
		}
		_ite_l=_team_ennemi.begin();
		while(end_team(_team_ennemi)){
			cout<<"\t\t\t\t\t\t\t\tTour ennemi"<<endl;
			//Luminy.display();
			for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++)
			{
				(*_ite)->set_paCurrent(0);
			}
		}
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			(*_ite)->set_paCurrent((*_ite)->get_paMax());
		}
	}
	cout << " Combat Fini, tout le monde est mort " << endl;
}

#define DEPLACER 1
#define TIRER 2
#define CC 3
#define CHANGER 4
/** La méthode allieTour définit le tour de l'allié et indique si c'est la fin du tour
 	 * @param &endTour - adresse du booléen qui indique si c'est la fin du tour ou pas
 	 * */
void Partie::allieTour(bool &endTour){
	int choix;
	bool endGame; 						// booléen indiquant la fin du jeu
	cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
	do{
		cout<<"\t\t\t\t\t\t\t\tPerso ("<<(*_ite_l)->get_x()<<","<<(*_ite_l)->get_y()<<")"<<endl;
		cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*_ite_l)->get_paCurrent()<<endl;
		(*_ite_c).display();								// affichage de la carte
		choix = main_switch();								// choix de l'action à faire
		switch (choix){
			case DEPLACER :
				endGame = this->move_choice(1);
				break;
			case TIRER :
				endTour = this->shoot_choice();
				break;
			case CC :
				endTour = this->close_combat_choice();
				break;
			case CHANGER :
				if( _team_hero.size() == 1 ){
					cout<<"Vous n'avez qu'un seul perso!";
				} else if( (*_ite_l) == _team_hero.back() ){
					_ite_l = _team_hero.begin();
				} else {
					_ite_l++;
				}
				break;
		}
	} while( choix != 0 && !endGame );
	// reinitialisation des PA de la team Hero
	for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){
		(*_ite)->set_paCurrent(0);
	}
}

/** La méthode main_switch invite le joueur à choisir une action à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
int Partie::main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps à Corps " << endl;
		cout << " " << CHANGER << " - Changer de Personnage " << endl;
		cout << " Tapez 0 pour passer votre tour \n> ";
		cin >> reponse ;
	} while ( reponse < 0 || reponse > CHANGER ) ;
	return( reponse ) ;
}

#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14
#define EXIT 10
/** La méthode move_choice gère le déplacement du héros en action dans le tour.
 	 * @param withUsePA - boolean qui indique si le mouvement consomme des PA.
 	 * @return elle retourne 1 si on quitte le jeu ou 0 sinon
 	 * */
bool Partie::move_choice(bool withUsePA){
	int choix;
	do{
		choix = move_switch();
		switch(choix){
		case NORTH:
			(*_ite_c).move_up(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EAST:
			(*_ite_c).move_right(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case SOUTH:
			(*_ite_c).move_down(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case WEST:
			(*_ite_c).move_left(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EXIT:
			return 1;
			break;
		}
	} while (choix != 10);
	return 0;
}

/** La méthode move_switch invite le joueur à choisir le déplacement à faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
int Partie::move_switch ( void ){
	int reponse ;
	do {
		cout << "\n\t\t\t\t\tOu voulez vous allez : \n\t\t\t\t\t" << NORTH << " - au Nord " << endl;
		cout << "\t\t\t\t\t" << EAST  << " - a l'Est " << endl;
		cout << "\t\t\t\t\t" << SOUTH << " - au Sud " << endl;
		cout << "\t\t\t\t\t" << WEST << " - a l'Ouest " << endl;
		cout << "\t\t\t\t\tTapez 10 pour quitter le jeu \n> ";
		cin >> reponse ;
	} while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

/** La méthode shoot_choice gère le système de tir à distance du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
bool Partie::shoot_choice( void ){
	if((*_ite_l)->get_paCurrent()>=4){
		list<Personnage*> in_range;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite_c).pathIsPossible((*_ite_l)->get_x(),(*_ite_l)->get_y(),(*_ite)->get_x(),(*_ite)->get_y())){
				in_range.push_front((*_ite));
			}
		}
		(*_ite_l)->shoot(in_range);
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){
				temp.push_front(*_ite);
			} else {
				(*_ite_c).removeItem(*(*_ite));
			}
		}
		_team_ennemi=temp;
		if(_team_ennemi.size()==0){
			return true;
		}
	}
	return false;
}

/** La méthode close_combat_choice gère le système de tir au càc du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
bool Partie::close_combat_choice( void ){
	if((*_ite_l)->get_paCurrent()>=3){
		list<Personnage*> proch = (*_ite_l)->near(_team_ennemi);
		(*_ite_l)->close_combat(proch);
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){
				temp.push_front(*_ite);
			} else {
				(*_ite_c).removeItem(*(*_ite));
			}
		}
		_team_ennemi=temp;
		if(_team_ennemi.size()==0){
			return true;
		}
	} else {
		cout<<"Pas assez de PA!"<<endl;
	}
	return false;
}

/** La méthode end_team indique si la team à fini son tour
 	 * @return elle retourne "vrai" si c'est le cas et "false" sinon
 	 * */
bool Partie::end_team(list<Personnage*> team)
{
	if(team.size()==0){
		return(0);
	}
	list<Personnage*>::iterator ite;
	for(ite=team.begin();ite!=team.end();ite++){
		if((*ite)->get_paCurrent()==0){
			return(0);
		}
	}
	return(1);
}

// le destructeur
Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

