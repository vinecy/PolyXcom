/*
 * Partie.h
 *
 *  Created on: 16 d�c. 2016
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
private:								// ATTRIBUTS
	list<Ennemi> 		_tank_ennemi;		// conteneurs pour
	list<Hero>			_tank_hero;			// le chargement a partir d'un fichier
	list<Obstacle>  	_tank_obstacle;
	list<string>  		_collec_carte;		// liste de toutes les cartes du jeu
	list<Portail>  		_tank_portail;

	list<Personnage*>	_team_hero;			// equipe de heros
	list<Personnage*>	_team_ennemi;		// equipe de ennemi

	Carte 				_mapCurrent;		// carte actuel

	list<Personnage*>::iterator _ite_l;		// it�rateur de personnage en action
	list<Personnage*>::iterator _ite;		// iterateur divers
	list<Ennemi>::iterator 		_ite_e;		// iterateur ennemi
	list<Hero>::iterator 		_ite_h;		// iterateur hero
	list<Obstacle>::iterator 	_ite_o;		// iterateur obstacle
	list<string>::iterator 		_ite_nm;	// iterateur nom de carte
	list<Portail>::iterator		_ite_p;		// iterateur de portail
public:
	Partie();							// CONSTRUCTEUR
										// METHODES
	void newPartie( void );					// r�initialise la sauvegarde
	void loadPartie( void );				// charge la sauvegarde
	void launchPartie( void );				// lance le jeu � partir de la sauvegarde charg�
	void savePartie( void );				// sauvegarde la partie

	void switchMap( Portail p );// change de carte actuel
	void explorationMode( void );			// d�finit le mode exploration

	void fightMode( void );					// d�finit le mode combat
	void allieTour( bool & );				// d�finit le tour du joueur
	int main_switch ( void );				// invite le joueur au choix de l'action � faire
	int move_choice( bool withUsePA );		// g�re le d�placement du personnage selon le mode
	bool bonus_choice( void );
	int move_switch ( void );				// invite le joueur au choix du mouvement � faire
	bool shoot_choice( void );				// g�re le choix de la cible � attaquer � distance
	bool close_combat_choice( void );		// g�re le choix de la cible � attaquer au corps � corps
	bool end_team(list<Personnage*> team);	// indique si la team est KO

	virtual ~Partie();					// DESTRUCTEUR
};

#endif /* PARTIE_H_ */
