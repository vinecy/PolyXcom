/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'�l�ves de Polytech Marseille. Il ne peut �tre
 * reproduit, utilis� ou modifi� sans l'avis express de ses auteurs.
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
 * @brief La classe Partie permet de g�rer la partie du joueur, la gestion des item, des cartes,
 * des ennemis, des heros, etc.
 */

#include "Partie.h"
#include "Fichier.h"

using namespace std;

/** Le constructeur Partie cr�e la partie en cours
  * */
Partie::Partie() {
	cout << " + Partie construite " << endl;
}

/** La m�thode newPartie permet d'initialiser le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::newPartie(void){
	Fichier pathFile("Save",1); 				// ouverture en lecture et ecriture de la sauvegarde
	pathFile.cleanFile();						// init de la sauvegarde
	pathFile.writeFile("mapCurrent: Luminy");	// r�ecriture du fichier initiale
	//TODO faire une copie du fichier de r�f�rence pour l'init d'une sauvegarde

}

/** La m�thode loadPartie permet de charger le fichier contenant la sauvegarde
  * du joueur
  * */
void Partie::loadPartie(void){
	Fichier pathMap("World",0); 	// ouverture en lecture de la carte
	Fichier pathFile("Save",1); 	// ouverture en lecture et ecriture de la sauvegarde
	list<Ennemi>::iterator ite_e;	// it�rateur d'ennemi
	list<Hero>::iterator   ite_h;	// it�rateur de h�ros
	string nameCurrentMap;			// nom de la carte actuel

	pathFile.seekMapCurrent(nameCurrentMap);// recherche de la carte actuel dans la sauvegarde
	pathMap.seekAllMap(_collec_carte);		// recherche de toutes les autres cartes
	// chargement de la carte actuel
	pathMap.loadMap(nameCurrentMap, _tank_carte, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	// it�rateur sur la carte actuel
	_ite_c = _tank_carte.begin();
	while( ( (*_ite_c).get_nameMap() != nameCurrentMap )
		&& ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		(*_ite_c).addItem((*_ite_e));
	}
	// ajout des h�ros sur la carte
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
	// initialisation de la team de h�ros sur la carte actuel
	for(ite_h = _tank_hero.begin() ; ite_h != _tank_hero.end() ; ite_h++){
		_team_hero.push_front( &(*ite_h) );
	}
}

/** La m�thode launchPartie permet de lancer le jeu en fonction de la sauvegarde
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

	//TODO trouver algorithme qui place les h�ros sur la map vers le portail



	/*// maj de la coord du h�ro
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

/** La m�thode explorationMode d�finit le mode exploration du jeu
  * */
void Partie::explorationMode(void){
	cout << " Mode exploration " << endl;
	bool endGame = false,					// bool�en indiquant la fin du jeu
		 acrossNewMap = 0;					// bool�en indiquant si on franchit une nouvelle carte
	//int heroX,heroY;						// coordonn�es du h�ro

	while(!acrossNewMap && !endGame){
		_ite_l = _team_hero.begin();		// it�rateur sur le h�ros principal
		(*_ite_c).display();				// affichage de la carte
		endGame = this->move_choice(0);				// choix du mouvement � faire
		/*


		// TODO les compagnons suivent le h�ros principal
		heroX = (*_ite_l)->get_x();
		heroY = (*_ite_l)->get_y();
		_ite_l++; 							// c'est un compagnon � partir du deuxi�me �l�ment de la liste
		while(_ite_l != _team_hero.end()){
			(*_ite_c).moveItemToWithMoveAnim( (*_ite_l)->get_x(), (*_ite_l)->get_y(), heroX, heroY);
			_ite_l++;						// heros suivant
		}*/
	}
}

/** La m�thode fightMode d�finit le mode combat du jeu
  * */
void Partie::fightMode(void){
	bool endFight = 0;						// bool�en qui indique si c'est la fin du combat
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
/** La m�thode allieTour d�finit le tour de l'alli� et indique si c'est la fin du tour
 	 * @param &endTour - adresse du bool�en qui indique si c'est la fin du tour ou pas
 	 * */
void Partie::allieTour(bool &endTour){
	int choix;
	bool endGame; 						// bool�en indiquant la fin du jeu
	cout<<"\t\t\t\t\t\t\t\tTour alli�"<<endl;
	do{
		cout<<"\t\t\t\t\t\t\t\tPerso ("<<(*_ite_l)->get_x()<<","<<(*_ite_l)->get_y()<<")"<<endl;
		cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*_ite_l)->get_paCurrent()<<endl;
		(*_ite_c).display();								// affichage de la carte
		choix = main_switch();								// choix de l'action � faire
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

/** La m�thode main_switch invite le joueur � choisir une action � faire
 	 * @return elle retourne le choix saisit par le joueur
 	 * */
int Partie::main_switch ( void ){
	int reponse ;
	do {
		cout << "\nQue voulez-vous faire : \n " << DEPLACER << " - Se deplacer " << endl;
		cout << " " << TIRER  << " - Tirer " << endl;
		cout << " " << CC << " - Corps � Corps " << endl;
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
/** La m�thode move_choice g�re le d�placement du h�ros en action dans le tour.
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

/** La m�thode move_switch invite le joueur � choisir le d�placement � faire
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

/** La m�thode shoot_choice g�re le syst�me de tir � distance du h�ros en action dans le tour.
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

/** La m�thode close_combat_choice g�re le syst�me de tir au c�c du h�ros en action dans le tour.
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

/** La m�thode end_team indique si la team � fini son tour
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

