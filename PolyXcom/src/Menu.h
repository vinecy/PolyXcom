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
	RectangleShape bouton[3];		// GRAPHIQUES
	Text text[3];
	Color selected;
	Color unSelected;
	Image i;
	Texture t;
	Sprite logo;
	Font font;

	std::vector<Drawable> listDrawable;

	//Partie jeu;					// JEU
	bool valide;
	int choix;

public:
	Menu();

	void Init();
	void CleanUp();

	void Pause();
	void Resume();

	void HandleEvents(IHMmanager* game);
	void Update(IHMmanager* game);
	void Draw(IHMmanager* game);

	virtual ~Menu();
};

#endif /* MENU_H_ */
