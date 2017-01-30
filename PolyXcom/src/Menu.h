/*
 * Menu.h
 *
 *  Created on: 14 janv. 2017
 *      Author: Valentin BISSUEL
 */

#ifndef MENU_H_
#define MENU_H_

#include "IHMstate.h"
#include <SFML/Graphics.hpp>

class Menu : public IHMstate{
private:						// ATTRIBUTS
									// GRAPHIQUES
	RectangleShape bouton[3];		// bouton "nouvelle Partie", "Charger Partie", "Quitter la Partie"
	Text text[3];					// texte des boutons "nouvelle Partie", "Charger Partie", "Quitter la Partie"
	Image i;						// Fichier contenant la feuille de Sprite
	Texture t;						// Texture chargé à partir la feuille de Sprite
	Sprite logo;					// Image correspondant au logo et chargé à partir de la texture
	Font font;						// Police de caractère

	//Partie jeu;					// JEU
	bool valide;					// indique si le choix est valide
	int choix;						// entier correspondant au choix

public:
	Menu();						// CONSTRUCTEUR
								// METHODES herités de IHMState
	void Init();							// Initialisation de l"etat
	void CleanUp();							// Nettoyage de l'Etat

	void Pause();							// Méthode déclenché lorsque l'état est en pause
	void Resume();							// Méthode déclenché lorsque l"état reprend

	void HandleEvents(IHMmanager* game);	// Maj de la détection des événements exterieur
	void Update(IHMmanager* game);			// Maj des variables
	void Draw(IHMmanager* game);			// Maj de l'écran

	virtual ~Menu();		 	// DESTRUCTEUR
};

#endif /* MENU_H_ */
