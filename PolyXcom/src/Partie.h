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
#include "IHMstate.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Partie : public IHMstate {
private:								// ATTRIBUTS
										// GRAPHIQUES
	int choix = 0;							// entier indiquant quel bouton est selectionné
	int choixYesNo = 0;						// entier indiquant si le bouton Oui ou Non est sélectionné
	int fenetreActive;						// entier indiquant quel fenêtre est active
	bool valide;							// booléen indiquant si le clic se fait bien sur un bouton
	bool premiereApparition;
										//STATES
	bool STATE_CC;							// actif si on est en mode "corps à corps"
	bool STATE_TIR;							// actif si on est en mode "tir"
	bool STATE_GRE;							// actif si on est en mode "grenade"
										// JEU
	list<Ennemi> 		_tank_ennemi;		// liste des ennemis présent sur la carte
	list<Hero>			_tank_hero;			// liste des héros encore vivant
	list<Obstacle>  	_tank_obstacle;		// liste des obstacles présent sur la carte
	list<Portail>  		_tank_portail;		// liste des portails présent sur la carte
	list<Portail>  		_tank_portail_close;// liste des portails condammés

	list<Hero*>			_team_hero;			// equipe de heros
	list<Ennemi*>		_team_ennemi;		// equipe de ennemi

	Carte 				_mapCurrent;		// carte actuelle

	list<Hero*>::iterator _ite_l;			// itérateur de personnage en action
	list<Personnage*>::iterator _ite;		// iterateur divers
	list<Ennemi>::iterator 		_ite_e;		// iterateur ennemi
	list<Ennemi*>::iterator 	_ite_ee;	// iterateur ennemi
	list<Hero>::iterator 		_ite_h;		// iterateur hero
	list<Obstacle>::iterator 	_ite_o;		// iterateur obstacle
	list<Portail>::iterator		_ite_p;		// iterateur de portail

public:
	Partie(int);							// CONSTRUCTEUR
											// METHODES Hérités de IHMstate
	void Init();								// Initialise les composants de l'interface graphique
	void InitHUD();								// Initialise les boutons, compteur de PV,PA,munitions
	void InitMenuInvent();						// Initialise la fenêtre "Ouvrir Inventaire"
	void InitMenuCarte();						// Initialise la fenêtre "Ouvrir Carte"
	void InitMenuStats();						// Initialise la fenêtre "Consulter les statistiques"
	void InitMenuQuitter();						// Initialise la fenêtre "Quitter la partie"

	void CleanUp();								// Vide tous les conteneurs
	void Pause();								// Instructions liés à la mise en pause de la partie
	void Resume();								// Instructions liés à la remise en route de la partie

	void HandleEvents(IHMmanager* game);		// Maj à des évenenements clavier

	void Update(IHMmanager* game);				// Maj des variables
	void UpdateHUD(IHMmanager* game);			// Maj des boutons, compteurs,...
	void UpdateMenuInvent(IHMmanager* game);	// Maj des composants du menu "Ouvrir Inventaire"
	void UpdateMenuCarte(IHMmanager* game);		// Maj des composants du menu "Ouvrir Carte"
	void UpdateMenuStats(IHMmanager* game);		// Maj des composants du menu "Consulter les statistiques"
	void UpdateMenuQuitter(IHMmanager* game);	// Maj des composants du menu "Quitter la partie"
	void UpdateMap(IHMmanager* game);			// Maj des composants de l'écran de jeu

	void Draw(IHMmanager* game);				// Redessine la fenetre
	void DrawHUD(IHMmanager* game);				// Redessine les boutons,compteurs, etc
	void DrawActiveFrame(IHMmanager* game);		// Reddesine la fenetre active
	void DrawMap(IHMmanager* game);				// Redessine les éléments de l'écran de jeu
										// METHODES
	void newPartie( void );					// réinitialise la sauvegarde
	void loadPartie( void );				// charge la sauvegarde
	void launchPartie( void );				// lance le jeu à partir de la sauvegarde chargé
	void savePartie( void );				// sauvegarde la partie

	void switchMap( Portail p, bool ban );	// change de carte actuel
	void explorationMode( void );			// définit le mode exploration

	void fightMode( void );					// définit le mode combat
	void allieTour( bool & );				// définit le tour du joueur
	int main_switch ( void );				// invite le joueur au choix de l'action à faire
	int move_choice( bool withUsePA );		// gère le déplacement du personnage selon le mode
	bool bonus_choice( void );
	bool reload( void );
	int move_switch ( void );				// invite le joueur au choix du mouvement à faire
	bool shoot_choice( void );				// gère le choix de la cible à attaquer à distance
	bool close_combat_choice( void );		// gère le choix de la cible à attaquer au corps à corps
	bool end_team(list<Personnage*> team);	// indique si la team est KO

	virtual ~Partie();					// DESTRUCTEUR
};

#endif /* PARTIE_H_ */
