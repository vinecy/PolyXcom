/*
 * Partie.h
 *
 *  Created on: 16 déc. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include "Ennemi.h"
#include "Hero.h"
#include "Obstacle.h"
#include "Carte.h"
#include "Portail.h"
#include "Fichier.h"

using namespace std;


class Partie {
private:
	list<Ennemi> 		_tank_ennemi;	// conteneurs pour
	list<Hero>			_tank_hero;		// le chargement a partir d'un fichier
	list<Obstacle>  	_tank_obstacle;
	list<Carte>  		_tank_carte;		// conteneur de cartes (l'actuel + les suivantes)
	list<string>  		_collec_carte;	// liste de toutes les cartes du jeu
	list<Portail>  		_tank_portail;	// conteneur de cartes (l'actuel + les suivantes)

	list<Personnage*>	_team_hero;		// equipes de personnages
	list<Personnage*>	_team_ennemi;


	list<Personnage*>::iterator _ite_l;	// itérateur de personnage qui agit
	list<Personnage*>::iterator _ite;	// iterateur divers
	list<Ennemi>::iterator 		_ite_e;	// iterateur ennemi
	list<Hero>::iterator 		_ite_h;	// iterateur hero
	list<Obstacle>::iterator 	_ite_o;	// iterateur obstacle
	list<Carte>::iterator 		_ite_c;	// iterateur carte11
	list<string>::iterator 		_ite_nm;	// iterateur carte11

public:
	Partie();

	void newPartie( void );
	void loadPartie( void );
	void launchPartie( void );
	void savePartie( void );

	void switchMap( void );
	void explorationMode( void );

	void fightMode( void );
	void allieTour( bool & );
	int main_switch ( void );
	void move_choice( bool withUsePA );
	int move_switch ( void );
	bool shoot_choice( void );
	bool bonus_choice( void );
	bool close_combat_choice( void );
	bool end_team(list<Personnage*> team);

	virtual ~Partie();
};

#endif /* PARTIE_H_ */
