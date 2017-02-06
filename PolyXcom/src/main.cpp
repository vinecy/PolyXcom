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

#include <iostream>				// Bibliothèque pour la console
#include <SFML/Graphics.hpp>	// Bibliothèque multimédia
#include "IHMmanager.h"			// Appel de la contrôleur
#include "Menu.h"				// Appel de l'Etat Menu

int main(){
	cout << " lancement de PolyXcom " << endl;

	RenderWindow window( VideoMode( VideoMode::getDesktopMode().width
								  , VideoMode::getDesktopMode().height
								  , VideoMode::getDesktopMode().bitsPerPixel)
						, "PolyXcom"
						, Style::Close | Style::Titlebar | Style::Fullscreen );
	IHMmanager ihm(window);
	ihm.PushState( new Menu() );

	while( ihm.isRunning() ){		// tant que la fenêtre est toujours ouvert
		ihm.HandleEvents();			// maj des evenements externes
		ihm.Update();				// maj des variables
		ihm.Draw();					// maj de la fenêtre
	}
}
