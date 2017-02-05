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
#include "IHMstate.h"
#include <SFML/Graphics.hpp>

using namespace std;


class Partie : public IHMstate {
private:								// ATTRIBUTS
										// GRAPHIQUES
	int choix = 0;
	int choixYesNo = 0;
	int fenetreActive;
	bool valide;
	bool premiereApparition;
										//STATES
	bool STATE_CC;
	bool STATE_TIR;
	bool STATE_GRE;
										// JEU
	list<Ennemi> 		_tank_ennemi;		// conteneurs pour
	list<Hero>			_tank_hero;			// le chargement a partir d'un fichier
	list<Obstacle>  	_tank_obstacle;
	list<Portail>  		_tank_portail;
	list<Portail>  		_tank_portail_close;

	list<Hero*>	_team_hero;			// equipe de heros
	list<Ennemi*>	_team_ennemi;		// equipe de ennemi

	Carte 				_mapCurrent;		// carte actuelle

	list<Hero*>::iterator _ite_l;		// it�rateur de personnage en action
	list<Personnage*>::iterator _ite;		// iterateur divers
	list<Ennemi>::iterator 		_ite_e;		// iterateur ennemi
	list<Ennemi*>::iterator 	_ite_ee;		// iterateur ennemi
	list<Hero>::iterator 		_ite_h;		// iterateur hero
	list<Obstacle>::iterator 	_ite_o;		// iterateur obstacle
	list<Portail>::iterator		_ite_p;		// iterateur de portail

public:
	Partie(int);							// CONSTRUCTEUR
										// METHODES H�rit�s
	void Init();
	void InitHUD();
	void InitMenuInvent();
	void InitMenuCarte();
	void InitMenuStats();
	void InitMenuQuitter();

	void CleanUp();
	void Pause();
	void Resume();

	void HandleEvents(IHMmanager* game);

	void Update(IHMmanager* game);
	void UpdateHUD(IHMmanager* game);
	void UpdateMenuInvent(IHMmanager* game);
	void UpdateMenuCarte(IHMmanager* game);
	void UpdateMenuStats(IHMmanager* game);
	void UpdateMenuQuitter(IHMmanager* game);
	void UpdateMap(IHMmanager* game);

	void Draw(IHMmanager* game);
	void DrawHUD(IHMmanager* game);
	void DrawActiveFrame(IHMmanager* game);
	void DrawMap(IHMmanager* game);
										// METHODES
	void newPartie( void );					// r�initialise la sauvegarde
	void loadPartie( void );				// charge la sauvegarde
	void launchPartie( void );				// lance le jeu � partir de la sauvegarde charg�
	void savePartie( void );				// sauvegarde la partie

	void switchMap( Portail p, bool ban );	// change de carte actuel
	void explorationMode( void );			// d�finit le mode exploration

	void fightMode( void );					// d�finit le mode combat
	void allieTour( bool & );				// d�finit le tour du joueur
	int main_switch ( void );				// invite le joueur au choix de l'action � faire
	int move_choice( bool withUsePA );		// g�re le d�placement du personnage selon le mode
	bool bonus_choice( void );
	bool reload( void );
	int move_switch ( void );				// invite le joueur au choix du mouvement � faire
	bool shoot_choice( void );				// g�re le choix de la cible � attaquer � distance
	bool close_combat_choice( void );		// g�re le choix de la cible � attaquer au corps � corps
	bool end_team(list<Personnage*> team);	// indique si la team est KO

	virtual ~Partie();					// DESTRUCTEUR
};

#endif /* PARTIE_H_ */
