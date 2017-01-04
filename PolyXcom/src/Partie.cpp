/*
 * Partie.cpp
 *
 *  Created on: 16 déc. 2016
 *      Author: Valentin BISSUEL
 */

#include "Partie.h"
#include "Fichier.h"

using namespace std;

Partie::Partie() {
	cout << " + Partie construite " << endl;
}


void Partie::newPartie(void){
	Fichier pathFile("Save",1); // ouverture en lecture et ecriture
	pathFile.cleanFile();
	pathFile.writeFile("mapCurrent: Luminy");
}

void Partie::loadPartie(void){
	Fichier pathMap("World",0); // ouverture en lecture
	Fichier pathFile("Save",1); // ouverture en lecture et ecriture
	list<Ennemi>::iterator ite_e;
	list<Hero>::iterator   ite_h;
	string nameCurrentMap;

	pathFile.loadFile(nameCurrentMap);
	pathMap.seekMap(_collec_carte);
	pathMap.loadMap(nameCurrentMap, _tank_carte, _tank_ennemi, _tank_hero, _tank_obstacle, _tank_portail);

	for(ite_e = _tank_ennemi.begin(); ite_e != _tank_ennemi.end(); ite_e++){
			_team_ennemi.push_front( &(*ite_e) );
	}
	for(ite_h = _tank_hero.begin(); ite_h != _tank_hero.end(); ite_h++){
		_team_hero.push_front( &(*ite_h) );
	}
	_ite_c = _tank_carte.begin();
	while( ( (*_ite_c).get_nameMap() != "Luminy" ) && ( _ite_c != _tank_carte.end()) ){
		_ite_c++;
	}
}

void Partie::launchPartie(void){
	bool exitGame = 0,
		 thisDangerZone = (*_ite_c).get_dangerZone();
	while(!exitGame){
		if( thisDangerZone == true ){
			cout << " Alerte! Ennemi en vue! " << endl;
			this->fightMode();
			thisDangerZone = false;
		} else {
			cout << " RAS " << endl;
			this->explorationMode();
		}
		//exitGame = true;
	}
}

void Partie::savePartie(void){

}

void Partie::switchMap(void){

}

void Partie::explorationMode(void){
	cout << " Mode exploration " << endl;
	/*bool acrossNewMap = 0;
	while(!acrossNewMap){
		(*_ite_c).display();
		this->move_choice(0);
	}*/
}

void Partie::fightMode(void){
	bool endFight = 0;
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
#define BONUS 4
#define CHANGER 5

void Partie::allieTour(bool &endTour){
	int choix;
	cout<<"\t\t\t\t\t\t\t\tTour allié"<<endl;
	do{
		cout<<"\t\t\t\t\t\t\t\tPerso "<<(*_ite_l)->get_x()<<"/"<<(*_ite_l)->get_y()<<endl;
		cout<<"\t\t\t\t\t\t\t\tPA restants= "<<(*_ite_l)->get_paCurrent()<<endl;
		(*_ite_c).display();

		choix = main_switch();
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
	} while( choix != 0 );
	for(_ite=_team_hero.begin();_ite!=_team_hero.end();_ite++){
		(*_ite)->set_paCurrent(0);
	}
}

#define NORTH 11
#define EAST 12
#define SOUTH 13
#define WEST 14
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

void Partie::move_choice(bool withUsePA){
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
		}
	} while (choix != 10);
}

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

bool Partie::bonus_choice( void ){
	if((*_ite_l)->get_paCurrent()>=2){
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

Partie::~Partie() {
	cout << " - Partie detruite " << endl;
}

