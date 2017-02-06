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
private:
	RenderWindow* _myWindow;
	vector<IHMstate*> _myStates;

public: float _scaleBouton;

public:
	IHMmanager(RenderWindow&);
	void Init();
	void CleanUp();

	void ChangeState(IHMstate* state);
	void PushState(IHMstate* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool isRunning(){ return (_myWindow->isOpen()); }
	RenderWindow* get_myWindow(){ return (_myWindow); }

	virtual ~IHMmanager();
};

#endif /* IHMMANAGER_H_ */
