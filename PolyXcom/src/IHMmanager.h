/*
 * IHMmanager.h
 *
 *  Created on: 14 janv. 2017
 *      Author: Valentin BISSUEL
 */

#ifndef IHMMANAGER_H_
#define IHMMANAGER_H_

#include <SFML/Graphics.hpp>				// Bibliothèque Mulimédia

using namespace sf;
using namespace std;

class IHMstate;

class IHMmanager : public RenderWindow{
private:									// ATTRIBUTS
	RenderWindow* _myWindow;					// Fenetre Windows active
	vector<IHMstate*> _myStates;				// Pile d'états IHMstate

public: float _scaleBouton;						// rapport de division de la taille des boutons

public:
	IHMmanager(RenderWindow&);				// CONSTRUCTEUR
	void Init();								// lance le protocole d'initialisation de l'etat actif
	void CleanUp();								// vide la pile d'états et ferme la fenêtre

	void ChangeState(IHMstate* state);			// remplace l'etat actuel par l'état mis en argument
	void PushState(IHMstate* state);			// ajoute un état au gestionnaire d'IHM
	void PopState();							// retire l'état courant de la pile d'Etat

	void HandleEvents();						// lance le protocole de maj des evenements externes de l'Etat Actif
	void Update();								// lance le protocole de maj des variables de l'etat actif
	void Draw();								// lance le protocole de maj de la fenêtre

	bool isRunning(){ return (_myWindow->isOpen()); }	// Determine si la fenêtre est toujours active
	RenderWindow* get_myWindow(){ return (_myWindow); } // Retourne l'état de la fenêtre active

	virtual ~IHMmanager();					// DESTRUCTEUR
};

#endif /* IHMMANAGER_H_ */
