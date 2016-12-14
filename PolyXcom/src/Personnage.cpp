/**
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
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
 */

/**
 * @file Personnage.cpp
 * @brief La classe Personnage est une sous classe d'Affichable, elle sert de base pour les humanoides
 */

#include "Personnage.h"
#include "Carte.h"
#include <iostream>
#include <list>

using namespace std;

Personnage::Personnage()
{
	_level=0;
	_pvMax=10;
	_paMax=10;
	_pvCurrent=10;
	_paCurrent=10;
	_strength=10;
	_accuracy=10;
	_agility=10;
	_endurance=10;
	_luck=10;
	_rotation=10;
	_inv_armes=Arme();
}

/** Le constructeur Personnage cree un personnage et initialise ses attributs
 	 * @param x - abscisse du perso
 	 * @param y - ordonnée du perso
 	 * @param ID - identifacteur
	 * @param pv - Points de Vie max du perso
	 * @param pa - Points d'Action max du perso
	 * @param arme - arme du perso*/
Personnage::Personnage(int x,int y,int ID,int lev,int str,int acc,int agi,int end,int luck,Arme arme):Affichable(x,y,ID)//construteur
{
	_level=lev;
	_pvCurrent=10;
	_paCurrent=10;
	_strength=str;
	_accuracy=acc;
	_agility=agi;
	_endurance=end;
	_luck=luck;
	_pvMax=str;
	_paMax=acc;
	_pvCurrent=_pvMax;
	_paCurrent=_paMax;
	_rotation=0;
	_inv_armes=arme;
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
int Personnage::get_rotation(void){
	return(_rotation);
}
Arme Personnage::get_inv_armes(void){
	return(_inv_armes);
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

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Personnage::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<_coordX<<" / Y="<<_coordY<<" )"<<endl;
	cout<<"PV( "<<_pvCurrent<<" / "<<_pvMax<<" )"<<endl;
	cout<<"PA( "<<_paCurrent<<" / "<<_pvMax<<" )"<<endl;
	_inv_armes.display_info();
	cout<<"///////////////"<<endl;
}

void Personnage::reload()
{
	_inv_armes.set_munCurrent(_inv_armes.get_munMax());
}


/** Le destructeur Personnage*/
Personnage::~Personnage()				//destructor
{
	cout << "Personnage detruit" << endl;
}
