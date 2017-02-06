/*
 * IHMmanager.cpp
 *
 *  Created on: 14 janv. 2017
 *      Author: Valentin BISSUEL
 */

#include "IHMmanager.h"
#include "IHMstate.h"

#include <iostream>
#include <SFML/Graphics.hpp>

/** Le constructeur IHMmanager initialise le gestionnaire d'états d'IHM
  * */
IHMmanager::IHMmanager(RenderWindow& w) {
	_myWindow = &w;

	if( (_myWindow->getSize().x >= 1920) && (_myWindow->getSize().y >= 1080)){
			_scaleBouton = 1 ;
	} else if( (_myWindow->getSize().x >= 1366) && (_myWindow->getSize().y >= 768)){
		_scaleBouton = 0.75 ;
	} else {
		_scaleBouton = 0.25;
	}

	cout << " + IHMmanager démarré" << endl;
}

/** La méthode CleanUp vide la pile d'états et ferme la fenêtre
  * */
void IHMmanager::CleanUp(){
	while( !_myStates.empty() ){
		delete(_myStates.back());
		PopState();
	}
	cout << "Fermeture de la fenêtre" << endl;
	_myWindow->close();
}

/** La méthode ChangeState change d'état actif en retirant le sommet de la pile et en ajoutant
  * l'état en argument dans la pile
  * */
void IHMmanager::ChangeState(IHMstate* state){
	if( !_myStates.empty() ){
		PopState();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

/** La méthode PushState ajoute l'état en argument dans la pile d'Etats
  * */
void IHMmanager::PushState(IHMstate* state){
	if( !_myStates.empty() ){
		_myStates.back()->Pause();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

/** La méthode PopState retire l'état actuel de la pile d'Etats
  * */
void IHMmanager::PopState(){
	_myStates.back()->CleanUp();

	if( !_myStates.empty() ){
		delete(_myStates.back());
		_myStates.pop_back();
		if( !_myStates.empty() ) _myStates.back()->Resume();
	}
}

/** La méthode HandleEvents lance la méthode de maj des evenements externes de l'Etat Actif
  * */
void IHMmanager::HandleEvents(){
	if(!_myStates.empty()){
		_myStates.back()->HandleEvents(this);
	}
}

/** La méthode Update lance la méthode de maj des variables de l'etat actif
  * */
void IHMmanager::Update(){
	if(!_myStates.empty()){
		_myStates.back()->Update(this);
	}
}

/** La méthode Update lance la méthode de maj de la fenêtre
  * */
void IHMmanager::Draw(){
	if(!_myStates.empty()){
		_myStates.back()->Draw(this);
	}
}

/** La destructeur détruit l'objet
  * */
IHMmanager::~IHMmanager() {
	cout << " - IHMmanager terminé" << endl;
}

