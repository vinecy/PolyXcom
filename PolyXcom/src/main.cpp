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
#include <fstream>			// Bibliothèque pour les fichiers
#include "Partie.h"			// Main utilise la classe Partie pour le chargement du jeu.
#include <SFML/Graphics.hpp>
#include <unistd.h>

using namespace sf;

int chooseMain();			// gère le choix de l'action à faire par le joueur

int main(){
	cout << " lancement de PolyXcom " << endl;
/********************A DEPLACER*************/

	/*Thread thread( &chooseMain );
	thread.launch();*/
/*
	RenderWindow window(VideoMode(1366,720,32),"PolyXcom",
							Style::Close |
							Style::Titlebar |
							!Style::Fullscreen |
							Style::Resize);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Image image2;
	Texture image;
	Sprite sprite;
	Sprite logo;
	if( !image2.loadFromFile("src\\sprite.png") ){
		cout << "erreur de fichier" << endl;
	} else {
		image2.createMaskFromColor(Color::White);
		image.create(image2.getSize().x, image2.getSize().y);
		image.update(image2);
		image.setSmooth(true);
		sprite.setTexture(image);
	}
	sprite.setTextureRect(IntRect(1,1,63,63));
	sprite.setPosition(50, 50);

	//nt i = 0;
	while(window.isOpen()){
		Event event;

		while(window.pollEvent(event)){			// dès qu'un evenement est déclenché
			if(event.type == Event::Closed){	// si on demande la fermeture
				window.close();					// on ferme la fenetre
			}
		}

		window.clear();			// on vide l'écran

		sprite.move(Vector2f(1,0));
		window.draw(sprite);

		window.display();		// on affiche
	}
	*/
	/* ********* NOUVEAU ***************/

	Partie game;					// Partie contenant le jeu à l'etat actuel
	bool valide = 0;			// booléan indiquant si le jeu est fini ou non (initialement faux)
	int choix = 0;						// variable indiquant le n° de choix du joueur
	RenderWindow window(VideoMode(1366,720,32),"PolyXcom",
								Style::Close |
								Style::Titlebar |
								Style::Resize);
	// Paramètres de la fenêtre
	window.setFramerateLimit(60);

	// Element du menu principal
	RectangleShape newPartie(Vector2f(300,100));
	RectangleShape loadPartie(Vector2f(300,100));
	RectangleShape exitPartie(Vector2f(300,100));

	int espacement = 5;
	newPartie.setFillColor( Color(160,160,160));
	loadPartie.setFillColor(Color(160,160,160));
	exitPartie.setFillColor(Color(160,160,160));
	newPartie.setPosition( ((window.getSize().x)/2 - ((newPartie.getSize().x)/2))
						  , (window.getSize().y)/2  );
	loadPartie.setPosition(((window.getSize().x)/2 - ((loadPartie.getSize().x)/2))
						  , newPartie.getPosition().y + newPartie.getSize().y + espacement );
	exitPartie.setPosition(((window.getSize().x)/2 - ((exitPartie.getSize().x)/2))
						  ,loadPartie.getPosition().y + loadPartie.getSize().y + espacement );


	Image image2;
	Texture image;
	Sprite sprite;
	Sprite bouton[3];

	if( !image2.loadFromFile("src\\sprite.png") ){
		cout << "erreur de fichier" << endl;
	} else {
		image2.createMaskFromColor(Color::White);
		image.create(image2.getSize().x, image2.getSize().y);
		image.update(image2);
		image.setSmooth(true);

		sprite.setTexture(image); sprite.setTextureRect(IntRect(1,1,63,63));
		bouton[0].setTexture(image); bouton[0].setTextureRect(IntRect(1,131,197,65)); bouton[0].setScale(2, 2);
		bouton[1].setTexture(image); bouton[1].setTextureRect(IntRect(1,131,197,65)); bouton[1].setScale(2, 2);
		bouton[2].setTexture(image); bouton[2].setTextureRect(IntRect(1,131,197,65)); bouton[2].setScale(2, 2);

		sprite.setPosition(50, 50);
		bouton[0].setPosition( (window.getSize().x)/2 ,
							   (window.getSize().y)/2 + 70);
	    bouton[1].setPosition( (window.getSize().x)/2 ,
	    					   (window.getSize().y)/2 + 140);
		bouton[2].setPosition( (window.getSize().x)/2 ,
							   (window.getSize().y)/2 + 210);
	}



	int x,y;

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){			// dès qu'un evenement est déclenché
			switch (event.type) // Type de l'évènement
			{
				case Event::Closed : // Bouton de fermeture
					window.close();
					break;
				case Event::KeyReleased : // Appui sur une touche du clavier
				{
					switch (event.key.code) // La touche qui a été appuyée
					{
						case Keyboard::Up:  // Echap
							choix--;
							if(choix == 0) choix = 3;
							break;
						case Keyboard::Escape: // Echap
							window.close();
							break;
						case Keyboard::Down : // Echap
							choix++;
							if(choix == 4) choix = 1;
							break;
						case Keyboard::Return : // Echap
							valide = true;
							break;
						default :
							break;
					}
					break;
				}
				case Event::MouseMoved :
					x = event.mouseMove.x;
					y = event.mouseMove.y;
					if( newPartie.getGlobalBounds().contains(x, y) == true ){
						choix = 1;
					} else if( loadPartie.getGlobalBounds().contains(x, y) == true ){
						choix = 2;
					} else if( exitPartie.getGlobalBounds().contains(x, y) == true ){
						choix = 3;
					} else {
						choix = 0; valide = false;
					}
					break;
				case Event::MouseButtonPressed :
					if( event.mouseButton.button == Mouse::Left ){
						valide = true;
					}
					break;
				default :
					break;
			}
		}

		if( choix == 1 ) newPartie.setFillColor(Color(0,0,160));
		else newPartie.setFillColor(Color(160,160,160));
		if( choix == 2 ) loadPartie.setFillColor(Color(0,0,160));
		else loadPartie.setFillColor(Color(160,160,160));
		if( choix == 3 ) exitPartie.setFillColor(Color(0,0,160));
		else exitPartie.setFillColor(Color(160,160,160));

		if(valide == true){
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
					window.close();		// fin
				break;
			}
			valide = false;
		}
		window.clear();

		sprite.move(Vector2f(1,0));
		window.draw(sprite);
		window.draw(newPartie);
		window.draw(loadPartie);
		window.draw(exitPartie);
		window.draw(bouton[0]);
		window.draw(bouton[1]);
		window.draw(bouton[2]);

		window.display();		// on affiche
	}

	/* *******************ANCIEN*************
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
	}
	*/

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


