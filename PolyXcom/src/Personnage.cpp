/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
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
 */

/**
 * @file Personnage.cpp
 * @brief La classe Personnage est une sous classe d'Affichable, elle sert de base pour les humanoides
 */

#include "Personnage.h"
#include <iostream>
#include <list>

using namespace std;

/** Le constructeur Personnage cree un personnage et initialise ses attributs
 	 * @param x - abscisse du perso
 	 * @param y - ordonnée du perso
 	 * @param ID - identifacteur
	 * @param pv - Points de Vie max du perso
	 * @param pa - Points d'Action max du perso
	 * @param arme - arme du perso*/
Personnage::Personnage(int x,int y,int ID,int pv,int pa,list<Arme> l)	//construteur
{
	_coordX=x;
	_coordY=y;
	_ID=ID;
	_pvMax=pv;
	_paMax=pa;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
	_rotation=0;
	list<Arme> _inv_armes=l;
}

int Personnage::get_pvMax(void)			//getters
{
	return(_pvMax);
}
int Personnage::get_paMax(void)
{
	return(_paMax);
}
int Personnage::get_pvCurrent(void)
{
	return(_pvCurrent);
}
int Personnage::get_paCurrent(void)
{
	return(_paCurrent);
}

void Personnage::set_pvMax(int pv)		//setters
{
	_pvMax=pv;
}
void Personnage::set_paMAx(int pa)
{
	_paMax=pa;
}
void Personnage::set_pvCurrent(int pv)
{
	_pvCurrent=pv;
}
void Personnage::set_paCurrent(int pa)
{
	_paCurrent=pa;
}

/** La methode Personnage deplace un pero vers de Nord
	 * @param map - carte sur laquelle le perso bouge*/
void Personnage::move_up(Carte &map)
{
	if(map.moveIsPossible(_coordX,_coordY+1))
	{
		map.moveItemTo( _coordX , _coordY , _coordX , _coordY+1);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
/** La methode Personnage deplace un pero vers le Sud
	 * @param map - carte sur laquelle le perso bouge*/
void Personnage::move_down(Carte &map)
{
	if(map.moveIsPossible(_coordX,_coordY-1))
	{
		map.moveItemTo(_coordX , _coordY , _coordX , _coordY-1);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
/** La methode Personnage deplace un pero vers l'Ouest
	 * @param map - carte sur laquelle le perso bouge*/
void Personnage::move_left(Carte &map)
{
	if(map.moveIsPossible(_coordX-1,_coordY))
	{
		map.moveItemTo(_coordX , _coordY , _coordX-1,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}
/** La methode Personnage deplace un pero vers l'Est
	 * @param map - carte sur laquelle le perso bouge*/
void Personnage::move_right(Carte &map)
{
	if(map.moveIsPossible(_coordX+1,_coordY))
	{
		map.moveItemTo(_coordX , _coordY , _coordX+1,_coordY);
	}
	else
	{
		cout<<"erreur"<<endl;
	}
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Personnage::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}

/** Le destructeur Personnage*/
Personnage::~Personnage()				//destructor
{
	cout << "Personnage detruit" << endl;
}
