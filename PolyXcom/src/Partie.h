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
	int choix = 0;							// entier indiquant quel bouton est selectionn�
	int choixYesNo = 0;						// entier indiquant si le bouton Oui ou Non est s�lectionn�
	int fenetreActive;						// entier indiquant quel fen�tre est active
	bool valide;							// bool�en indiquant si le clic se fait bien sur un bouton
	bool premiereApparition;
										//STATES
	bool STATE_CC;							// actif si on est en mode "corps � corps"
	bool STATE_TIR;							// actif si on est en mode "tir"
	bool STATE_GRE;							// actif si on est en mode "grenade"
										// JEU
	list<Ennemi> 		_tank_ennemi;		// liste des ennemis pr�sent sur la carte
	list<Hero>			_tank_hero;			// liste des h�ros encore vivant
	list<Obstacle>  	_tank_obstacle;		// liste des obstacles pr�sent sur la carte
	list<Portail>  		_tank_portail;		// liste des portails pr�sent sur la carte
	list<Portail>  		_tank_portail_close;// liste des portails condamm�s

	list<Hero*>			_team_hero;			// equipe de heros
	list<Ennemi*>		_team_ennemi;		// equipe de ennemi

	Carte 				_mapCurrent;		// carte actuelle

	list<Hero*>::iterator _ite_l;			// it�rateur de personnage en action
	list<Personnage*>::iterator _ite;		// iterateur divers
	list<Ennemi>::iterator 		_ite_e;		// iterateur ennemi
	list<Ennemi*>::iterator 	_ite_ee;	// iterateur ennemi
	list<Hero>::iterator 		_ite_h;		// iterateur hero
	list<Obstacle>::iterator 	_ite_o;		// iterateur obstacle
	list<Portail>::iterator		_ite_p;		// iterateur de portail

public:
	Partie(int);							// CONSTRUCTEUR
											// METHODES H�rit�s de IHMstate
	void Init();								// Initialise les composants de l'interface graphique
	void InitHUD();								// Initialise les boutons, compteur de PV,PA,munitions
	void InitMenuInvent();						// Initialise la fen�tre "Ouvrir Inventaire"
	void InitMenuCarte();						// Initialise la fen�tre "Ouvrir Carte"
	void InitMenuStats();						// Initialise la fen�tre "Consulter les statistiques"
	void InitMenuQuitter();						// Initialise la fen�tre "Quitter la partie"

	void CleanUp();								// Vide tous les conteneurs
	void Pause();								// Instructions li�s � la mise en pause de la partie
	void Resume();								// Instructions li�s � la remise en route de la partie

	void HandleEvents(IHMmanager* game);		// Maj � des �venenements clavier

	void Update(IHMmanager* game);				// Maj des variables
	void UpdateHUD(IHMmanager* game);			// Maj des boutons, compteurs,...
	void UpdateMenuInvent(IHMmanager* game);	// Maj des composants du menu "Ouvrir Inventaire"
	void UpdateMenuCarte(IHMmanager* game);		// Maj des composants du menu "Ouvrir Carte"
	void UpdateMenuStats(IHMmanager* game);		// Maj des composants du menu "Consulter les statistiques"
	void UpdateMenuQuitter(IHMmanager* game);	// Maj des composants du menu "Quitter la partie"
	void UpdateMap(IHMmanager* game);			// Maj des composants de l'�cran de jeu

	void Draw(IHMmanager* game);				// Redessine la fenetre
	void DrawHUD(IHMmanager* game);				// Redessine les boutons,compteurs, etc
	void DrawActiveFrame(IHMmanager* game);		// Reddesine la fenetre active
	void DrawMap(IHMmanager* game);				// Redessine les �l�ments de l'�cran de jeu
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
