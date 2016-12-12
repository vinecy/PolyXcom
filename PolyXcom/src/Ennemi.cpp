/*
 * Ennemi.cpp
 *
 *
 *  Created on: 27 nov. 2016
 *      Author: Vincent
 */

#include "Ennemi.h"

using namespace std;
Ennemi::Ennemi()
{

}

/** Le constructeur Ennemi cree un ennemi et initialise ses attributs
	 * @param x - Points de Vie max du perso
	 * @param y - Points d'Action max du perso
	 * @param ID - Type de l'ennemi
	 * @param pvMax - Points de Vie max du perso
	 * @param paMax - Points d'Action max du perso
	 * @param arme - Arme par defaut de l'ennemi*/
Ennemi::Ennemi(int x,int y,int ID,int pv,int pa,Arme arme):Personnage(x,y,ID,pv,pa,arme)
{
}

/** La méthode display_info permet d'afficher les attributs de celui qui l'invoque dans la console */
void Ennemi::display_info(void)
{
	cout<<"///////////////"<<endl;
	cout<<"Coord( X="<<this->get_x()<<" / Y="<<this->get_y()<<" )"<<endl;
	cout<<"PV( "<<this->get_pvCurrent()<<" / "<<this->get_pvMax()<<" )"<<endl;
	cout<<"PA( "<<this->get_paCurrent()<<" / "<<this->get_paMax()<<" )"<<endl;
	cout<<"///////////////"<<endl;
}
/** La méthode begin AI commence l'algorithme de choix de laction par l'AI*/
void Ennemi::begin_IA()
{
	cout<<"begin!"<<endl;
}

list<Personnage*> Ennemi::near(Carte &map,list<Personnage*> team)
{
	list<Personnage*>::iterator ite;
	list<Personnage*> l;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if(((((*ite)->get_x()+1==_coordX)||((*ite)->get_x()-1==_coordX))&&((*ite)->get_y()==_coordY)))
		{
			l.push_front((*ite));
		}
		else if(((((*ite)->get_y()+1==_coordY)||((*ite)->get_y()-1==_coordY))&&((*ite)->get_x()==_coordX)))
		{
			l.push_front((*ite));
		}
	}
	return(l);
}

/** Le destructeur Ennemi*/
Ennemi::~Ennemi()				//destructor
{
	cout << "Personnage ennemi" << endl;
}

