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
	cout << " + IHMmanager démarré" << endl;
}

void IHMmanager::CleanUp(){
	while( !_myStates.empty() ){
		PopState();
	}
	_myWindow->close();
}

void IHMmanager::ChangeState(IHMstate* state){
	if( !_myStates.empty() ){
		_myStates.pop_back();
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
	if( !_myStates.empty() ){
		_myStates.back()->CleanUp();
		_myStates.pop_back();
		_myStates.back()->Resume();
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

