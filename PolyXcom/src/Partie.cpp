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
Partie::Partie(int choix) {
	cout << " + Partie construite " << endl;
	if( choix == 1 ){
		newPartie();		// reinitialisation de la sauvegarde
		loadPartie();		// chargement du jeu
		launchPartie();		// lancement du jeu
	} else if( choix == 2 ){
		loadPartie();		// chargement du jeu
		launchPartie();		// lancement du jeu
	} else {
		cout << "ERREUR: choix erroné" << endl;
	}
}

/*** ******************************************************************************************************** ***/
/*** *********************** METHODES HERITES DE IHMstate *************************************************** ***/
/*** ******************************************************************************************************** ***/

void Partie::Init(){

}
/*
void Cleanup(){
	cout << " ... Fermeture du Menu " << endl;
}*/

void Partie::Pause(){

}

void Partie::Resume(){
	Init();
}

void Partie::HandleEvents(IHMmanager* game){


}
void Partie::Update(IHMmanager* game){

}

void Partie::Draw(IHMmanager* game){

}

/*** ******************************************************************************************************** ***/
/*** ******************************************************************************************************** ***/
/*** ******************************************************************************************************** ***/

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
	string nameCurrentMap;			// nom de la carte actuel

	pathFile.seekMapCurrent(nameCurrentMap);// recherche de la carte actuel dans la sauvegarde
	// chargement de la carte actuel
	pathMap.loadMap(nameCurrentMap, _mapCurrent, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	// itérateur sur la carte actuel
	/*_ite_c = _tank_carte.begin();
	while( ( _mapCurrent.get_nameMap() != nameCurrentMap )
		&& ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}*/

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		_mapCurrent.addItem((*_ite_e));
	}
	// ajout des héros sur la carte
	// TODO Hero codé en dur temporairement. ils sont issu normalement de la save
	_tank_hero.push_front(Hero(0,0,2,0,10,11,12,13,14,Inventaire(),"Vincent"));
	_tank_hero.push_front(Hero(0,1,2,0,9,10,11,12,13,Inventaire(),"Alexis"));
	for(_ite_h = _tank_hero.begin(); _ite_h!=_tank_hero.end(); _ite_h++){
		_mapCurrent.addItem((*_ite_h));
	}

	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		_mapCurrent.addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		_mapCurrent.addItem((*_ite_p));
		(*_ite_p).display();
	}
	// initialisation de la team d'ennemis sur la carte actuel
	_team_ennemi.clear();
	for(_ite_e = _tank_ennemi.begin() ; _ite_e != _tank_ennemi.end() ; _ite_e++){
		_team_ennemi.push_front( &(*_ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	_team_hero.clear();
	for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
		_team_hero.push_front( &(*_ite_h) );
	}
}

/** La méthode launchPartie permet de lancer le jeu en fonction de la sauvegarde
  * */
void Partie::launchPartie(void){
	bool exitGame = 0,									// boolean indiquant si on quitte le jeu
		 isDangerZone = _mapCurrent.get_dangerZone();	// boolean indiquant si on est en zone de combat ou non
	while(!exitGame){
		if( isDangerZone == true ){ 					// mode Combat
			cout << " Alerte! Ennemi en vue! " << endl;
			this->fightMode();
			//isDangerZone = false;
			cout << "gain de niveau " << endl;
		} else {										// mode Exploration
			cout << " RAS " << endl;
			this->explorationMode();
		}
		isDangerZone = _mapCurrent.get_dangerZone();
		//exitGame = true;
	}
}
// TODO
void Partie::savePartie(void){

}

/** La méthode switchMap permet de changer de carte actuel à partir des données fourni par le
  * portail p
  	  * @param p - portail où le joueur se situe qui engendre le changement de carte*/
void Partie::switchMap( Portail p ){
	_mapCurrent.removeAllItem();							// on retire tous le monde de la carte sans toucher au conteneur
	Fichier pathMap("World",0);							// chargement de la prochaine map
	cout << "chargement de la map" << endl;
	pathMap.loadMap(p.get_nameNextMap(), _mapCurrent, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);
	cout << "iterateur sur la map" << endl;
	/*_ite_c = _tank_carte.begin();						// itérateur sur la nouvelle carte
	while( ( _mapCurrent.get_nameMap() != p.get_nameNextMap() )
		&& ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}*/
	_mapCurrent.display();

	// ajout des ennemis sur la carte
	for(_ite_e = _tank_ennemi.begin();_ite_e!=_tank_ennemi.end();_ite_e++){
		_mapCurrent.addItem((*_ite_e));
	}

	// ajout des obstacles sur la carte
	for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++){
		_mapCurrent.addItem((*_ite_o));
	}
	// ajout des portail sur la carte
	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		_mapCurrent.addItem((*_ite_p));
		(*_ite_p).display();
	}

	_mapCurrent.display();
	// recherche des points de spawn disponibles sur la carte
	cout << "recherche des spawn pour héros sur "<< p.get_newX() << "," << p.get_newY() << endl;
	list<pair<int,int> > spawnList = _mapCurrent.seekSpawnPoint(p.get_newX(), p.get_newY(), 3);
	list<pair<int,int> >::iterator ite = spawnList.begin();
	for( ; ite != spawnList.end() ; ite++ ){
		cout << (*ite).first << "," << (*ite).second << endl;
	}

	// màj des coordonnées des héros sur la nouvelle carte
	ite = spawnList.begin();
	for(_ite_h = _tank_hero.begin();_ite_h!=_tank_hero.end();_ite_h++){
		(*_ite_h).set_x((*ite).first); (*_ite_h).set_y((*ite).second);
		ite++;
	}
	// ajout des héros sur la carte
	for(_ite_h = _tank_hero.begin();_ite_h!=_tank_hero.end();_ite_h++){
		_mapCurrent.addItem((*_ite_h));
	}
	_mapCurrent.display();
	// initialisation de la team d'ennemis sur la carte actuel
	_team_ennemi.clear();
	for(_ite_e = _tank_ennemi.begin() ; _ite_e != _tank_ennemi.end() ; _ite_e++){
		_team_ennemi.push_front( &(*_ite_e) );
	}
	// initialisation de la team de héros sur la carte actuel
	_team_hero.clear();
	for(_ite_h = _tank_hero.begin() ; _ite_h != _tank_hero.end() ; _ite_h++){
		_team_hero.push_front( &(*_ite_h) );
	}
}

/** La méthode explorationMode définit le mode exploration du jeu
  * */
void Partie::explorationMode(void){
	cout << " Mode exploration " << endl;
	int rep;
	bool endGame = 0,						// booléen indiquant si on quitte le jeu ou non
		 acrossNewMap = 0;					// booléen indiquant si on franchit une nouvelle carte ou non
	//int heroX,heroY;						// coordonnées du héro

	_ite_l = _team_hero.begin();			// itérateur sur le héros principal car il est le seul à se déplacer
	_ite_l++;								// on retire les compagnons de la carte
	while( _ite_l != _team_hero.end()){
		_mapCurrent.removeItem(*(*_ite_l));
		_ite_l++;
	}
	_ite_h = _tank_hero.end();
	_ite_l = _team_hero.begin();

	while(!acrossNewMap && !endGame){
		_mapCurrent.display();				// affichage de la carte
		rep = this->move_choice(0);			// choix du mouvement à faire
		if( rep == -1 ){					// si le joueur décide de quitter la partie
			cout << "Si vous quittez maintenant sans avoir sauvegarder la partie,";
			cout << "vous risquez de perdre votre progression. Quitter ? (Y/N)";
			string ans;
			cin >> ans;
			if(ans == "Y") endGame = true;
		} else if( rep == 2 ){									// si on franchit une nouvelle Map,
			acrossNewMap = true;
			cout << "on franchit une nouvelle map " << endl;
			_mapCurrent.display();
			cout << "recherche du portail" << endl;
			_ite_p = _tank_portail.begin();						// recherche du portail correspondant
			cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
			cout << "position du heros : " <<   (*_ite_l)->get_x() << "," << (*_ite_l)->get_y() << endl;
			while( ( !( (*_ite_p).get_x() == (*_ite_l)->get_x() )&&( (*_ite_p).get_y() == (*_ite_l)->get_y()) )
				&& ( _ite_p != _tank_portail.end() )
			){
				_ite_p++;
			}
			cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
			int newX = (*_ite_p).get_newX(),					// on extrait les infos de ce portail
				newY = (*_ite_p).get_newX();
			string nameNextMap = (*_ite_p).get_nameNextMap();
			cout << "ce portail pointe vers " << newX << "," << newY << "dans" << nameNextMap << endl;
			cout << "début du switch" << endl;

			switchMap((*_ite_p));
		}
	}
}

/** La méthode fightMode définit le mode combat du jeu
  * */
void Partie::fightMode(void){
	bool endFight = 0;						// booléen qui indique si c'est la fin du combat
	cout << " Mode Combat " << endl;

	while(!endFight){
		cout << "\t\t\t\t\t\t\t\tNouveau tour"<<endl;
		_ite_l = _team_hero.begin();		//_ite_l est le personnage actuel
		while(end_team(_team_hero)){		//tour des heros
			this->allieTour(endFight);
		}
		for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){//fin du tour: reinitialisation des PA
			(*_ite)->set_paCurrent((*_ite)->get_paMax());
		}
		_ite_l=_team_ennemi.begin();		//_ite_l est l'ennemi actuel
		while(end_team(_team_ennemi)){		//tour des ennemis
			cout<<"\t\t\t\t\t\t\t\tTour ennemi"<<endl;
			for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++)
			{
				(*_ite)->set_paCurrent(0);	//mise a 0 des PA des ennemis (passe le tour) TODO IA
			}
		}
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			(*_ite)->set_paCurrent((*_ite)->get_paMax());//fin du tour: reinitialisation des PA
		}
	}
	cout << " Combat Fini, tout le monde est mort " << endl;

	for(_ite_p=_tank_portail.begin();_ite_p!=_tank_portail.end();_ite_p++){
		(*_ite_p).display();
	}


	cout << "recherche du portail" << endl;
	_ite_p = _tank_portail.begin();						// recherche du portail correspondant
	(*_ite_p).display();
	(*_ite_p).display_info();
	cout << "position du portail : " << (*_ite_p).get_x() << "," << (*_ite_p).get_y() << endl;
	int newX = (*_ite_p).get_newX(),					// on extrait les infos de ce portail
		newY = (*_ite_p).get_newY();
	string nameNextMap = (*_ite_p).get_nameNextMap();
	cout << "ce portail pointe vers " << newX << "," << newY << "dans" << nameNextMap << endl;
	cout << "début du switch" << endl;

	switchMap((*_ite_p));
}

#define DEPLACER 1
#define TIRER 2
#define CC 3
#define BONUS 4
#define CHANGER 5
/** La méthode allieTour définit le tour de l'allié et indique si c'est la fin du tour
 	 * @param &endTour - adresse du booléen qui indique si c'est la fin du tour ou pas
 	 * */
void Partie::allieTour(bool &endTour){
	int choix;
	cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
	do{
		cout<<"\t\t\t\t\t\t\t\tPerso ("<<(*_ite_l)->get_x()<<","<<(*_ite_l)->get_y()<<")"<<endl;
		cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*_ite_l)->get_paCurrent()<<endl;
		_mapCurrent.display();								// affichage de la carte
		choix = main_switch();								// choix de l'action à faire
		switch (choix){
			case DEPLACER :
				this->move_choice(1);
				break;
			case TIRER :
				endTour = this->shoot_choice();
				break;
			case CC :
				endTour = this->close_combat_choice();
				break;
			case BONUS :
				endTour = this->bonus_choice();
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
	} while( choix != 0 );
	// reinitialisation des PA de la team Hero (force la fin du tour)
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
		cout << " " << BONUS << " - Utiliser un Bonus " << endl;
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
 	 * @return elle retourne -1 si on annule l'action
	 * 						  0 si le déplacement est impossible
	 * 						  1 si le déplacement a fonctionné
	 * 						  2 si le déplacement engendre un changement de carte
 	 * */
int Partie::move_choice(bool withUsePA){
	int choix,rep;
	do{
		choix = move_switch();
		switch(choix){
		case NORTH:
			rep = _mapCurrent.move_up(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EAST:
			rep = _mapCurrent.move_right(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case SOUTH:
			rep = _mapCurrent.move_down(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case WEST:
			rep = _mapCurrent.move_left(*(*_ite_l), withUsePA);
			choix=10;
			break;
		case EXIT:
			rep = -1;
			break;
		}
	} while (choix != 10);
	return rep;
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
		cout << "\t\t\t\t\tTapez 10 pour annuler \n> ";
		cin >> reponse ;
	} while ( reponse < 10 || reponse > WEST ) ;
	return( reponse ) ;
}

/** La méthode shoot_choice gère le système de tir à distance du héros en action dans le tour.
 	 * @return elle retourne "vrai" si il n'y a plus d'ennemis et "false" sinon
 	 * */
bool Partie::shoot_choice( void ){
	if((*_ite_l)->get_paCurrent()>=4){
		list<Personnage*> in_range;	//creation de liste qui contiendra les ennemis a porte de tir
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if(_mapCurrent.pathIsPossible((*_ite_l)->get_x(),(*_ite_l)->get_y(),(*_ite)->get_x(),(*_ite)->get_y())){
				in_range.push_front((*_ite));
			}
		}
		(*_ite_l)->shoot(in_range);			//declanchement de l'action de tir
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){ //si des ennemis sont morts, il sont supprimes de team ennemi
				temp.push_front(*_ite);
			} else {
				_mapCurrent.removeItem(*(*_ite));
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
		list<Personnage*> proch = (*_ite_l)->near(_team_ennemi); 	//proch est la liste des ennemi adjacents
		(*_ite_l)->close_combat(proch);								//declanchement de l'action cac
		list<Personnage*> temp;
		for(_ite=_team_ennemi.begin();_ite!=_team_ennemi.end();_ite++){
			if((*_ite)->get_pvCurrent()>=1){						//si des ennemis sont morts, ils sont supprimes
				temp.push_front(*_ite);
			} else {
				_mapCurrent.removeItem(*(*_ite));
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

bool Partie::bonus_choice( void ){
	int choice;
	cout<<" Taper 1 pour utiliser un medkit\n Tapez 2 pour utiliser une grenade\n Taper 0 pour quiter\n>"<<endl;
	cin >> choice;
	if(choice==1)
	{
		(*_ite_l)->use_medkit();
		return false;
	}
	else if(choice==2)
	{
		//(*_ite_l)->get_inv().get_grenade().display_info();
		if((*_ite_l)->get_grenade().get_number()>=0)
		{
			int x;
			int y;
			cout<<" Entrer X puis Y\n>";		//demande au joueur ou il veux lancer la grenade
			cin >> x;
			cout<<" >";
			cin >> y;
			if(_mapCurrent.moveIsPossible(x,y,0)) //si il peux lancer la grenade
			{
				cout<<"possible!";
				list<Personnage*>::iterator p;
				int xcompt;
				int ycompt;
				for(xcompt=x-1;xcompt<x+1;xcompt++)
				{
					for(ycompt=y-1;ycompt<y+1;ycompt++)
					{
						if(_mapCurrent.get_IDin(xcompt, ycompt)==1)
						{
							for(_ite_o=_tank_obstacle.begin();_ite_o!=_tank_obstacle.end();_ite_o++)
							{
								if(((*_ite_o).get_x()==x)||((*_ite_o).get_y()==y))
								{
									(*_ite_o).set_destructible();//degats sur les obstacles
								}
							}
						}
						else if(_mapCurrent.get_IDin(xcompt, ycompt)==2)
						{
							for(p = _team_hero.begin() ; p != _team_hero.end() ; p++)
							{
								if((*p)->get_x()==x||(*p)->get_y()==y)
								{								//degats sur les personnages
									(*p)->set_pvCurrent((*p)->get_pvCurrent()-(*_ite_l)->get_grenade().get_dammage());
								}
							}
						}
					}
				}
				if(_team_ennemi.size()==0){
					return true;
				}
				return false;//TODO cas suicide
			}
		}
		return false;
	}
	else
	{
		return false;
	}
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
		if((*ite)->get_paCurrent()==0){//si tout les perso de la team ont 0 PA
			return(0);
		}
	}
	return(1);
}

// le destructeur
Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

