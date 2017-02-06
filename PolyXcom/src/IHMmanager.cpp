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

void IHMmanager::CleanUp(){
	while( !_myStates.empty() ){
		PopState();
	}
	cout << "Fermeture de la fenêtre" << endl;
	_myWindow->close();
}

void IHMmanager::ChangeState(IHMstate* state){
	if( !_myStates.empty() ){
		PopState();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

void IHMmanager::PushState(IHMstate* state){
	if( !_myStates.empty() ){
		_myStates.back()->Pause();
	}
	_myStates.push_back(state);
	_myStates.back()->Init();
}

void IHMmanager::PopState(){
	_myStates.back()->CleanUp();

	if( !_myStates.empty() ){
		//_myStates.pop_back();
		delete(_myStates.back());
		_myStates.pop_back();
		if( !_myStates.empty() ) _myStates.back()->Resume();
	}
}

void IHMmanager::HandleEvents(){
	if(!_myStates.empty()){
		_myStates.back()->HandleEvents(this);
	}

}

void IHMmanager::Update(){
	if(!_myStates.empty()){
		_myStates.back()->Update(this);
	}
}

void IHMmanager::Draw(){
	if(!_myStates.empty()){
		_myStates.back()->Draw(this);
	}
}

IHMmanager::~IHMmanager() {
	cout << " - IHMmanager terminé" << endl;
}

