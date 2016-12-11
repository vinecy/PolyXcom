/*
 * Ennemi.cpp
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

list<Personnage*> Ennemi::near(Carte &map,list<Personnage*> &team)
{
	list<Personnage*>::iterator ite;
	list<Personnage*> l;
	for(ite=team.begin();ite!=team.end();ite++)
	{
		if((((((*ite)->get_x()+1==_coordX)||((*ite)->get_x()-1==_coordX))&&((*ite)->get_y()==_coordY))&((*ite)->get_pvCurrent()>0)))
		{
			l.push_front((*ite));
		}
		else if((((((*ite)->get_y()+1==_coordY)||((*ite)->get_y()-1==_coordY))&&((*ite)->get_x()==_coordX))&((*ite)->get_pvCurrent()>0)))
		{
			l.push_front((*ite));
		}
	}
	return(l);
}

void Ennemi::close_combat(list<Personnage*> &team)
{
	list<Personnage*>::iterator ite;
	if(team.size()==0)
	{
		cout<<"Pas d'ennemi proche"<<endl;
	}else if(team.size()==1){
		team.front()->set_pvCurrent(team.front()->get_pvCurrent()-2);
		this->set_paCurrent(this->get_paCurrent()-3);
		team.front()->display_info();
	}else{
		ite=team.begin();
		cout<<"\t\tplus de 1 ennemi :"<<endl;
		int taille = team.size();
		int compteur=0;
		int choix3;
		int fini=0;
		while(!fini)
		{
			compteur++;
			cout<<"Ennemi sélectionné= "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
			cout<<"\t\t tapez 0 pour frapper cet ennemi"<<endl;
			cout<<"\t\t taper 1 pour changer d'ennemi"<<endl;
			cin>>choix3;
			if(!choix3)
			{
				if((*ite)->get_pvCurrent()>2)
				{
					(*ite)->set_pvCurrent((*ite)->get_pvCurrent()-2);
					cout<<"Ennemi touché! "<<(*ite)->get_pvCurrent()<<"/"<<(*ite)->get_pvMax()<<endl;
				}
				else
				{
					(*ite)->set_pvCurrent(0);
					cout<<"Ennemi mort!"<<endl;
				}
				this->set_paCurrent(this->get_paCurrent()-3);
				fini=1;
			}else{

				if(compteur!=taille)
				{
					ite++;
				}
				else{
					fini=1;
				}

			}
		}
	}
}
/** Le destructeur Ennemi*/
Ennemi::~Ennemi()				//destructor
{
	cout << "Personnage ennemi" << endl;
}

