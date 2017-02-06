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

/** Le constructeur IHMmanager initialise le gestionnaire d'�tats d'IHM
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

	cout << " + IHMmanager d�marr�" << endl;
}

/** La m�thode CleanUp vide la pile d'�tats et ferme la fen�tre
  * */
void IHMmanager::CleanUp(){
	while( !_myStates.empty() ){
		delete(_myStates.back());
		PopState();
	}
	cout << "Fermeture de la fen�tre" << endl;
	_myWindow->close();
}

/** La m�thode ChangeState change d'�tat actif en retirant le sommet de la pile et en ajoutant
  * l'�tat en argument dans la pile
  * */
void IHMmanager::ChangeState(IHMstate* state){
	if( !_myStates.empty() ){
		PopState();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

/** La m�thode PushState ajoute l'�tat en argument dans la pile d'Etats
  * */
void IHMmanager::PushState(IHMstate* state){
	if( !_myStates.empty() ){
		_myStates.back()->Pause();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

/** La m�thode PopState retire l'�tat actuel de la pile d'Etats
  * */
void IHMmanager::PopState(){
	_myStates.back()->CleanUp();

	if( !_myStates.empty() ){
		delete(_myStates.back());
		_myStates.pop_back();
		if( !_myStates.empty() ) _myStates.back()->Resume();
	}
}

/** La m�thode HandleEvents lance la m�thode de maj des evenements externes de l'Etat Actif
  * */
void IHMmanager::HandleEvents(){
	if(!_myStates.empty()){
		_myStates.back()->HandleEvents(this);
	}
}

/** La m�thode Update lance la m�thode de maj des variables de l'etat actif
  * */
void IHMmanager::Update(){
	if(!_myStates.empty()){
		_myStates.back()->Update(this);
	}
}

/** La m�thode Update lance la m�thode de maj de la fen�tre
  * */
void IHMmanager::Draw(){
	if(!_myStates.empty()){
		_myStates.back()->Draw(this);
	}
}

/** La destructeur d�truit l'objet
  * */
IHMmanager::~IHMmanager() {
	cout << " - IHMmanager termin�" << endl;
}

