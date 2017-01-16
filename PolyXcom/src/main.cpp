/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 *
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
 * @file main.c
 * @brief Le main permet de lancer le jeu, charger une partie, la reinitialiser ou quitter le jeu.
 */

#define NEWGAME 1
#define LOADGAME 2
#define EXIT 3


#include <iostream>			// Bibliothèque pour ka console
#include "Partie.h"			// Main utilise la classe Partie pour le chargement du jeu.
#include <SFML/Graphics.hpp>
#include "IHMmanager.h"
#include "Menu.h"


int main(){
	cout << " lancement de PolyXcom " << endl;

	RenderWindow window( VideoMode(VideoMode::getDesktopMode().width
								  ,VideoMode::getDesktopMode().height
								  ,VideoMode::getDesktopMode().bitsPerPixel)
						, "PolyXcom"
						, Style::Close | Style::Titlebar );
	IHMmanager ihm(window);
	ihm.PushState( new Menu() );

	while(ihm.isRunning())
	{
		ihm.HandleEvents();
		ihm.Update();
		ihm.Draw();
	}
/*
>>>>>>> refs/remotes/origin/master
	Partie game;					// Partie contenant le jeu à l'etat actuel
	bool endPolyXcom = 0;			// booléan indiquant si le jeu est fini ou non (initialement faux)
	int choix;						// variable indiquant le n° de choix du joueur


	while(!endPolyXcom){
		do{
			choix = chooseMain();	// appel au choix de l'action à faire
			switch(choix){
				case NEWGAME:
					cout << " * Nouvelle Partie " << endl;
					game.newPartie();		// reinitialisation de la sauvegarde
					game.loadPartie();		// chargement du jeu
					game.launchPartie();	// lancement du jeu
					choix = 0;
				break;
				case LOADGAME:
					cout << " * Charger Partie " << endl;
					game.loadPartie();		// chargement du jeu
					game.launchPartie();	// lancement du jeu
				break;
				case EXIT:
					cout << " * Bye " << endl;
					endPolyXcom = 1;		// fin
				break;
			}
		} while( choix != EXIT );
	}*/
}

/* La fonction chooseMain permet de gérer le choix de l'action à faire par le joueur.
 	 * @return elle retourne le choix saisie par le joueur parmi les choix disponibles
 	 * */
int chooseMain ( void ){
	int reponse ;
	do {
		cout << "\n PolyXcom \n " << NEWGAME << " - Nouvelle Partie " << endl;
		cout << " " << LOADGAME  << " - Charger Partie " << endl;
		cout << " " << EXIT << " - Quitter \n  > ";
		cin >> reponse ;
	} while ( reponse < 0 || reponse > EXIT ) ;
	return( reponse ) ;
}
